@echo off

echo [objects] > temp.prj
echo %1.obj >> temp.prj

c:\projects\wladx_binaries_20040822\wla-65816 -o %1.asm %1.obj
c:\projects\wladx_binaries_20040822\wlalink -vr temp.prj %1.fig

del %1.obj
del temp.prj