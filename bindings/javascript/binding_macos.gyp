{
  "targets": [
    {
      "target_name": "tbi",
      "sources": [ "tbi_wrap.cxx", "tbi_core.cpp", "tbi_device.cpp", "tbi_service.cpp", "attribute.cpp", "tbit.cpp", "hid.c", "basicdemo.cpp", "chopper.cpp", "luke.cpp", "tbi_device_manager.cpp", "adc.cpp", "adc_hw.cpp", "gpio_hw.cpp", "i2c_hw.cpp", "pin.cpp"],
      "libraries": [ "-lstdc++ -framework IOKit -framework Carbon"],
    }
  ]
}
