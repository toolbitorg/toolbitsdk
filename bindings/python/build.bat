del /Q build
mkdir build
copy ..\..\include\*.h build
copy ..\..\include\module\*h build
copy ..\..\src\*.cpp build
copy ..\..\src\module\*.cpp build
copy ..\..\src\HIDAPI\windows\hid.c build
copy tbi.i build
copy setup_mswin.py build
xcopy /I/Y For_VC2008 build\For_VC2008
cd build
swig -c++ -python tbi.i

rem Please modify the following line according to your VC version
rem set VS90COMNTOOLS=%VS140COMNTOOLS%
python setup_mswin.py build_ext --inplace --swig-opts="-EHsc"

copy tbi.py ..\samples
copy _tbi.pyd ..\samples
cd ..
