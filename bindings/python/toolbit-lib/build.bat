mkdir toolbit
copy ..\..\..\include\*.h toolbit
copy ..\..\..\include\module\*.h toolbit
copy ..\..\..\src\module\*.cpp toolbit
copy ..\..\..\src\*.cpp toolbit
mkdir toolbit\macos
mkdir toolbit\linux
mkdir toolbit\mswin
copy ..\..\..\src\HIDAPI\linux\hid.c toolbit\linux
copy ..\..\..\src\HIDAPI\mac\hid.c toolbit\macos
copy ..\..\..\src\HIDAPI\windows\hid.c toolbit\mswin
copy ..\..\toolbit.i toolbit
cd toolbit; swig -c++ -python toolbit.i
move toolbit\toolbit.py toolbit\__init__.py
python setup.py build_ext --inplace
