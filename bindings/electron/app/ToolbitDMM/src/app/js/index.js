'use strict';

//console.debug = function(){/* NOP */};
//console.info = function(){/* NOP */};
//console.log = function(){/* NOP */};
//console.warn = function(){/* NOP */};
//console.error = function(){/* NOP */};

var moment=require('moment');
var Chartist=require('chartist');
require('chartist-plugin-zoom');

const TbiDeviceManager=require('./tbi.node').TbiDeviceManager;
const Luke=require('./tbi.node').Luke;
var tbiDeviceManager = new TbiDeviceManager();
console.log('The number of connected USB device: ' + tbiDeviceManager.getDeviceNum());
var luke = new Luke();

var dmmMode;
var dmmRange;
var timeInterval;
var holdChecked = false;
var graphChecked = false;
var clearGraph = false;
var runChecked = false;
var plotData = [];
var plotStart = new Date();

var setDmmMode = function(mode) {
  dmmMode = mode;
  console.log('dmmMode:' + mode);
};

var setDmmRange = function(range) {
  dmmRange = range;
  console.log('dmmRange:' + range);
};

var setTimeInterval = function(t) {
  if(t=='Fast') {
    timeInterval = 99;
  } else if(t=='Mid') {
    timeInterval = 999;
  } else if(t=='Slow') {
    timeInterval = 2999;
  };
  console.log('timeInterval:' + t);
};

var chartContainer = document.getElementById('chart-container');
var chart = new Chartist.Line(chartContainer, {}, {});

function exportData(records) {
   let data = JSON.stringify(records);
   let bom  = new Uint8Array([0xEF, 0xBB, 0xBF]);
   let blob = new Blob([bom, data], {type: 'text'});
   let url = (window.URL || window.webkitURL).createObjectURL(blob);
   let link = document.createElement('a');
   link.download = 'log-' + moment(plotStart).format('YYYYMMDD-HHmm') + '.json';
   link.href = url;
   document.body.appendChild(link);
   link.click();
   document.body.removeChild(link);
};

function disableElements(elems) {
  for(var i=0; i<elems.length; i++) {
    elems[i].disabled = true;
  }
}

function enableElements(elems) {
  for(var i=0; i<elems.length; i++) {
    elems[i].disabled = false;
  }
}

function openDevice() {
  if(!luke.open()) {
    // Polling connection of device
    window.setTimeout(openDevice, 3000);
    return;
  }
  clearGraph = true;

  setDmmMode(document.getElementById('mode').value);
  setDmmRange(document.getElementById('range').value);
  setTimeInterval(document.getElementById('interval').value);

  document.getElementById('mode').addEventListener('change', (event) => {
    setDmmMode(event.target.value);
    clearGraph = true;
  });
  document.getElementById('range').addEventListener('change', (event) => {
    setDmmRange(event.target.value);
  });
  document.getElementById('interval').addEventListener('change', (event) => {
    setTimeInterval(event.target.value);
    clearGraph = true;
  });
  document.getElementById('hold').addEventListener('change', function() {
    holdChecked = this.checked;
    console.log('holdChecked:' + holdChecked);
  });

  document.getElementById('run').addEventListener('change', function() {
    runChecked = this.checked;
    if(runChecked) {
      clearGraph = true;
      document.getElementById('save').disabled = false;
    }
    console.log('runChecked:' + runChecked);
  });
  document.getElementById('save').addEventListener('click', function() {
    exportData(plotData);
  });

  enableElements(document.getElementById('main').getElementsByTagName('input'));
  enableElements(document.getElementById('main').getElementsByTagName('select'));
  enableElements(document.getElementById('main').getElementsByTagName('button'));
  document.getElementById('save').disabled = true;

  window.setTimeout(acquisition, timeInterval);
}

function initialize() {
  disableElements(document.getElementById('main').getElementsByTagName('input'));
  document.getElementById('graph').disabled = false;
  disableElements(document.getElementById('main').getElementsByTagName('select'));
  disableElements(document.getElementById('main').getElementsByTagName('button'));
  document.getElementById('load').disabled = false;

  document.getElementById('graph').addEventListener('change', function() {
    graphChecked = this.checked;
    if(graphChecked) {
      document.getElementById('chart-container').className = '';
      document.getElementById('graph-menu').className = '';
      document.getElementById('run').click();
      window.resizeBy(0, 436);
    } else {
      document.getElementById('chart-container').className = 'hide';
      document.getElementById('graph-menu').className = 'hide';
      if(document.getElementById('run').checked) {
        document.getElementById('run').click();
      }
      window.resizeBy(0, -436);
    }
    console.log('graphChecked:' + graphChecked);
  });

  document.getElementById('load').addEventListener('click', function() {
    if(runChecked) {
      if(window.confirm("Is it OK to stop recording?")) {
        document.getElementById('run').click();
      } else {
        return;
      }
    }

    let fin = document.createElement('input');
    fin.type = 'file';
    fin.accept = '.json';
    fin.addEventListener('change', function(e) {
      var file = e.target.files[0];
      if(file.type.match('application/json')) {
        var reader = new FileReader();
        reader.addEventListener('load', function() {
          plotData = JSON.parse(this.result);
          console.log('Loaded plot data');
          drawGraph();
        })
      reader.readAsText(file);
      document.getElementById('save').disabled = true;
      }
    });
    fin.click();
  });

  openDevice();
};

function drawGraph() {
  var chart = new Chartist.Line(chartContainer,
  {  // data
    series: [
      {
        name: 'series-1',
        data: plotData
      }
    ]
  }, {  // options
    lineSmooth: false,
    showPoint: false,
    axisX: {
      type: Chartist.FixedScaleAxis,
      divisor: 5,
      labelInterpolationFnc: function(value) {
        if(moment(value).format("H")!=0) {
          return moment(value).format("H:m:ss.S");
        } else if(moment(value).format("m")!=0) {
          return moment(value).format("m:ss.S");
        }
        return moment(value).format("s.S");
      }
    },
    low: 0,
    plugins: [
      Chartist.plugins.zoom({
        resetOnRightMouseBtn: true,
//        onZoom: function(chart, reset) { storeReset(reset); }
      })
    ]
  });  // end of options
}

function acquisition() {
  window.setTimeout(acquisition, timeInterval);

  var val;
  var unit = '';
  var dispVal = document.getElementById('disp-val');
  var dispUnit = document.getElementById('disp-unit');

  if(dmmMode=='V') {
    val = luke.getVoltage();
  } else if(dmmMode=='A') {
    val = luke.getCurrent();
  };
  var t = new Date();

  if(clearGraph) {
    plotData.length = 0;
    plotData = [];
    clearGraph = false;
    plotStart = t;
  }

   if(runChecked) {
    var tdiff = t.getTime() - plotStart.getTime() + plotStart.getTimezoneOffset()*1000*60;
    plotData.push({x: tdiff, y: val});
  }

  if(!holdChecked) {

    if(dmmRange=='u') {
      val = val*1000000.0;
      unit = 'u';
    } else if(dmmRange=='m') {
      val = val*1000.0;
      unit = 'm';
    } else if(dmmRange=='Auto') {
      if(Math.abs(val)<0.001) {
        val = val*1000000.0;
        unit = 'u';
      }
      else if(Math.abs(val)<1.0) {
        val = val*1000.0;
        unit = 'm';
      }
    }

    var splitVal = String(Math.abs(val)).split('.');
    if(!splitVal[1]) {
      dispVal.value = val.toFixed(3);
    } else {
      var len = splitVal[0].length;
      if(len>4) {
        dispVal.value = Math.round(val);
      } else {
        dispVal.value = val.toFixed(4-len);
      }
    }
    dispUnit.value = unit + dmmMode;
    console.log('value[' + t.toJSON() + ']:' + dispVal.value);
  }

  if(runChecked) {
    drawGraph();
  }
};

document.addEventListener("DOMContentLoaded", function() {
  initialize();
});
