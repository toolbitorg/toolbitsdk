{
  "targets": [
    {
      "target_name": "toolbit",
      "sources": [ "toolbit_wrap.cxx", "tbi_core.cpp", "tbi_device.cpp", "tbi_service.cpp", "attribute.cpp", "tbit.cpp", "hid.c", "basicdemo.cpp", "chopper.cpp", "dmm.cpp", "tbi_device_manager.cpp", "adc.cpp", "adc_hw.cpp", "gpio_hw.cpp", "i2c_hw.cpp", "pin.cpp"],
      "libraries": [ "-ludev", "-lstdc++", "-lpthread", "-lrt" ],
    }
  ]
}
