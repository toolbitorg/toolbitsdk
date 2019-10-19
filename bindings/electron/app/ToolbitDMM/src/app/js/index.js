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
var clearPlotdata = false;
var plotdata = [{x: 0, y: 0}];
var counter = 0;

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
    timeInterval = 100;
  } else if(t=='Mid') {
    timeInterval = 1000;
  } else if(t=='Slow') {
    timeInterval = 3000;
  };
  console.log('timeInterval:' + t);
};

var chartContainer = document.getElementById('chart-container');
var chart = new CanvasJS.Chart(chartContainer, {
  animationEnabled: true,
  zoomEnabled: true,
  title: {
//    text: "Graph"
  },
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
  clearPlotdata = true;

  setDmmMode(document.getElementById('mode').value);
  setDmmRange(document.getElementById('range').value);
  setTimeInterval(document.getElementById('interval').value);

  document.getElementById('mode').addEventListener('change', (event) => {
    setDmmMode(event.target.value);
    clearPlotdata = true;
  });
  document.getElementById('range').addEventListener('change', (event) => {
    setDmmRange(event.target.value);
  });
  document.getElementById('interval').addEventListener('change', (event) => {
    setTimeInterval(event.target.value);
    clearPlotdata = true;
  });
  document.getElementById('hold').addEventListener('change', function() {
    holdChecked = this.checked;
    console.log('holdChecked:' + holdChecked);
  });
  document.getElementById('graph').addEventListener('change', function() {
    graphChecked = this.checked;
    if(graphChecked) {
      clearPlotdata = true;
      document.getElementById('chart-container').style.display = 'block';
      document.getElementById('graph-menu').style.display = 'block';
      window.resizeBy(0, 436);
    } else {
      document.getElementById('chart-container').style.display = 'none';
      document.getElementById('graph-menu').style.display = 'none';
      window.resizeBy(0, -436);
    }
    console.log('graphChecked:' + graphChecked);
  });
  document.getElementById('clear').addEventListener('click', function() {
    clearPlotdata = true;
    console.log('clearPlotdata: ' + clearPlotdata);
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

  if(clearPlotdata) {
    plotdata.length = 0;
    counter = 0;
    clearPlotdata = false;
  }

  if(graphChecked) {
    plotdata.push({x: counter,y: val});
    //plotdata.push({x: counter,y: counter})
    counter++;
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

    console.log('value:' + dispVal.value);
    if(graphChecked) {
      chart.render();
    }
  }
};

document.addEventListener("DOMContentLoaded", function() {
  initialize();
});
