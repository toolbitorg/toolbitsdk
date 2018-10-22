del /Q build
mkdir build
copy ..\..\include\*.h build
copy ..\..\include\module\*h build
copy ..\..\src\*.cpp build
copy ..\..\src\module\*.cpp build
copy ..\..\src\HIDAPI\windows\hid.c build
copy tbi.i build
copy binding_mswin.gyp build\binding.gyp
cd build
swig -c++ -javascript -node tbi.i
node-gyp configure build
copy /Y build\Release\tbi.node ..\samples
cd ..
