'use strict';

/*
const Chopper=require('./tbi.node').Chopper
var chopper = new Chopper();
*/
const Luke=require('./tbi.node').Luke
var luke = new Luke();

var dmmMode;
var timeInterval;
var holdChecked = false;
var graphChecked = false;
var plotdata = [{x: 0, y: 0}];
var counter = 0;


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


var setDmmMode = function(mode) {
  dmmMode = mode;
  console.log('dmmMode:' + mode);
  plotdata.length = 0;
};


var setTimeInterval = function(t) {
  if(t=='high') {
    timeInterval = 100;
  } else if(t=='mid') {
    timeInterval = 1000;
  } else if(t=='low') {
    timeInterval = 3000;
  };
  console.log('timeInterval:' + t);
};


var chartContainer = document.getElementById('chart-container');
var chart = new CanvasJS.Chart(chartContainer, {
  animationEnabled: true,
  zoomEnabled: true,
  title: {
    text: "Graph"
  },
  data: [{
    type: 'line',
    dataPoints: plotdata
  }]
});


function setupDmm() {

  setDmmMode(getRadioValue('rdbx-mode'));
  setTimeInterval(getRadioValue('rdbx-interval'));

  document.getElementById('rdbx-mode-v').addEventListener('change', function() {
    setDmmMode(getRadioValue('rdbx-mode'));
  });
  document.getElementById('rdbx-mode-c').addEventListener('change', function() {
    setDmmMode(getRadioValue('rdbx-mode'));
  });

  document.getElementById('rdbx-interval-high').addEventListener('change', function() {
    setTimeInterval(getRadioValue('rdbx-interval'));
  });
  document.getElementById('rdbx-interval-mid').addEventListener('change', function() {
    setTimeInterval(getRadioValue('rdbx-interval'));
  });
  document.getElementById('rdbx-interval-low').addEventListener('change', function() {
    setTimeInterval(getRadioValue('rdbx-interval'));
  });

  document.getElementById('chkbx-hold').addEventListener('change', function() {
    holdChecked = this.checked;
    console.log('holdChecked:' + holdChecked);
  });
  document.getElementById('chkbx-graph').addEventListener('change', function() {
    graphChecked = this.checked;
    console.log('graphChecked:' + graphChecked);
  });
};


function acquisition() {
  window.setTimeout(acquisition, timeInterval);

  var val;
  var disp = document.getElementById('disp');

  if(dmmMode=='voltage') {
    val = luke.getVoltage();
  } else if(dmmMode=='current') {
    val = luke.getCurrent();
  };

  if(graphChecked) {
    //plotdata.push({x: counter,y: val})
    plotdata.push({x: counter,y: counter})
    counter++;
  }

  if(!holdChecked) {
    disp.value = val;
    console.log('value:' + disp.value);
    if(graphChecked) {
      chart.render();
    }
  }
};


document.addEventListener("DOMContentLoaded", function() {
  setupDmm();
  window.setTimeout(acquisition, timeInterval);
});




/*
function setupChopper() {

  var _mychkbox1 = document.querySelector('input[name=myCheckbox1]');
  var _mychkbox2 = document.querySelector('input[name=myCheckbox2]');

  if(chopper.isConnected()) {

    _mychkbox1.disabled = false;
    _mychkbox2.disabled = false;

    _mychkbox1.checked = chopper.getUsbPortStatus() & 0x01;
    _mychkbox1.addEventListener('change', function() {
      if (_mychkbox1.checked) {
          chopper.enableUsbPort(1);
      } else {
          chopper.disableUsbPort(1);
      }
    });

    _mychkbox2.checked = chopper.getUsbPortStatus() & 0x02;
    _mychkbox2.addEventListener('change', function() {
      if (_mychkbox2.checked) {
          chopper.enableUsbPort(2);
      } else {
          chopper.disableUsbPort(2);
      }
    });

  } else {

    _mychkbox1.disabled = true;
    _mychkbox2.disabled = true;
    var timer = window.setTimeout(function() {
      chopper = new Chopper();
      setupChopper();
    }, 5000);

  }
}

document.addEventListener("DOMContentLoaded", setupChopper);
*/
