del *.h *.cpp *.so *.o *.cxx *.c tbi.py _tbi.pyd
copy ..\..\..\include\* .\
copy ..\..\..\include\module\* .\
copy ..\..\..\src\*.cpp .\
copy ..\..\..\src\module\*.cpp .\
copy ..\..\..\src\HIDAPI\windows\hid.c .\
copy For_VC2008\stdint.h .\
swig -c++ -python tbi.i

rem Please modify the following line according to your VC version
rem set VS90COMNTOOLS=%VS140COMNTOOLS%
python setup_mswin.py build_ext --inplace

copy tbi.py ..\samples
copy _tbi.pyd ..\samples
