del *.h *.cpp *.so *.o *.cxx *.c tbi.py _tbi.pyd
copy ..\..\..\include\* .\
copy ..\..\..\include\module\* .\
copy ..\..\..\src\*.cpp .\
copy ..\..\..\src\module\*.cpp .\
copy ..\..\..\src\HIDAPI\windows\hid.c .\
swig -c++ -python tbi.i

rem Please modify the following line according to your VC version
rem set VS90COMNTOOLS=%VS150COMNTOOLS%
set VS90COMNTOOLS="C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\Common7\Tools\"
python setup_mswin.py build_ext --inplace

copy tbi.py ..\samples
copy _tbi.pyd ..\samples
