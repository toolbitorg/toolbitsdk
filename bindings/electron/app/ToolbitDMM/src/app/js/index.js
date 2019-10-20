'use strict';

//console.debug = function(){/* NOP */};
//console.info = function(){/* NOP */};
//console.log = function(){/* NOP */};
//console.warn = function(){/* NOP */};
//console.error = function(){/* NOP */};

const TbiDeviceManager=require('./tbi.node').TbiDeviceManager
const Luke=require('./tbi.node').Luke
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
var plotdata = [{x: 0, y: 0}];
var plotStart = new Date();

/*
var getRadioValue = function(name) {
  var result = '';
  var elems = document.getElementsByName(name);

  for(var i=0, len=elems.length; i<len; i++) {
    var elem = elems.item(i);
    if(elem.checked) {
      result = elem.value;
      break;
    }
  }
  return result;
};
*/

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
var chart = new CanvasJS.Chart(chartContainer, {
  data: [{
    type: 'line',
    dataPoints: plotdata
  }]
});

function initialize() {

  if(!luke.open()) {
    // Polling connection of device
    window.setTimeout(initialize, 3000);
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
  document.getElementById('graph').addEventListener('change', function() {
    graphChecked = this.checked;
    if(graphChecked) {
      clearGraph = true;
      runChecked = true;
      document.getElementById('chart-container').className = '';
      document.getElementById('graph-menu').className = '';
      document.getElementById('run').checked = true;
      window.resizeBy(0, 436);
    } else {
      runChecked = false;
      document.getElementById('chart-container').className = 'hide';
      document.getElementById('graph-menu').className = 'hide';
      document.getElementById('run').checked = false;
      window.resizeBy(0, -436);
    }
    console.log('graphChecked:' + graphChecked);
    console.log('runChecked:' + runChecked);
  });
  document.getElementById('run').addEventListener('change', function() {
    runChecked = this.checked;
    if(runChecked) {
      clearGraph = true;
    }
    console.log('runChecked:' + runChecked);
  });

  window.setTimeout(acquisition, timeInterval);
};

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
    plotdata.length = 0;
    plotStart.setTime(t.getTime());
    clearGraph = false;
    // how to handle garbage??
    chart = new CanvasJS.Chart(chartContainer, {
      animationEnabled: true,
      zoomEnabled: true,
      title: {
    //    text: "Graph"
      },
      axisX: {
        valueFormatString: "s.f", labelAngle: 0
      },
      data: [{
        type: 'line',
        dataPoints: plotdata
      }]
    });
    chart.render();
  }

  if(runChecked) {
    t.setTime(t.getTime() - plotStart.getTime() + plotStart.getTimezoneOffset()*1000*60);
    plotdata.push({x: t, y: val});
    if(t.getHours()>0) {
        chart.options.axisX.valueFormatString = "H:m:ss.f";
    } else if(t.getMinutes()>0) {
      chart.options.axisX.valueFormatString = "m:ss.f";
    }
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

    console.log('value(' + t.toJSON() + '):' + dispVal.value);
  }
  if(runChecked) {
    chart.render();
  }
};

document.addEventListener("DOMContentLoaded", function() {
  initialize();
});
