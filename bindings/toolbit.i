%module toolbit

%include <stdint.i>
%include <std_string.i>
%include <std_vector.i>
%inline %{
using namespace std;
%}
%template(StringVector) std::vector<string>;

%{
#include "tbi_core.h"
#include "tbi_device.h"
#include "tbi_device_manager.h"
#include "tbi_service.h"
#include "attribute.h"
#include "tbit.h"
#include "hidapi.h"
#include "basicdemo.h"
#include "chopper.h"
#include "dmm.h"
#include "adc.h"
#include "adc_hw.h"
#include "gpio_hw.h"
#include "i2c_hw.h"
#include "pin.h"
%}

%include "tbi_core.h"
%include "tbi_device.h"
%include "tbi_device_manager.h"
%include "tbi_service.h"
%include "attribute.h"
%include "tbit.h"
%include "hidapi.h"
%include "basicdemo.h"
%include "chopper.h"
%include "dmm.h"
%include "adc.h"
%include "adc_hw.h"
%include "gpio_hw.h"
%include "i2c_hw.h"
%include "pin.h"
