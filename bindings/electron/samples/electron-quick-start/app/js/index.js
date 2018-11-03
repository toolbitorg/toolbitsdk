'use strict';

const Chopper=require('./tbi.node').Chopper
var chopper = new Chopper();

var onportEl = document.querySelector('.onport');
onportEl.addEventListener('click', function () {
  chopper.enableAllUsbPort();
});

var offportEl = document.querySelector('.offport');
offportEl.addEventListener('click', function () {
  chopper.disableAllUsbPort();
});
