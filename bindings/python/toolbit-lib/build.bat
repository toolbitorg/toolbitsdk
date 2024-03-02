mkdir toolbit
copy ..\..\..\include\*.h toolbit
copy ..\..\..\include\module\*.h toolbit
copy ..\..\..\src\module\*.cpp toolbit
copy ..\..\..\src\*.cpp toolbit
mkdir toolbit\macos
mkdir toolbit\linux
mkdir toolbit\mswin
copy ..\..\..\src\hidapi\linux\hid.c toolbit\linux
copy ..\..\..\src\hidapi\mac\hid.c toolbit\macos
copy ..\..\..\src\hidapi\windows\hid.c toolbit\mswin
copy ..\..\..\src\hidapi\windows\hid.c toolbit\mswin
copy ..\..\..\src\hidapi\windows\hidapi_winapi.h toolbit\mswin
copy ..\..\..\src\hidapi\windows\hidapi_cfgmgr32.h toolbit\mswin
copy ..\..\..\src\hidapi\windows\hidapi_hidclass.h toolbit\mswin
copy ..\..\..\src\hidapi\windows\hidapi_hidsdi.h toolbit\mswin
copy ..\..\..\src\hidapi\windows\hidapi_hidpi.h toolbit\mswin
copy ..\..\..\src\hidapi\windows\hidapi_descriptor_reconstruct.c toolbit\mswin
copy ..\..\..\src\hidapi\windows\hidapi_descriptor_reconstruct.h toolbit\mswin
copy ..\..\toolbit.i toolbit
cd toolbit
swig -c++ -python toolbit.i
move toolbit.py __init__.py
cd ..
python setup.py build_ext --inplace
