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
node-gyp rebuild --target=v3.0.5 --arch=x64 --dist-url=https://atom.io/download/electron
copy /Y build\Release\tbi.node ..\samples\
copy /Y build\Release\tbi.node ..\samples\electron-quick-start\app\
cd ..
