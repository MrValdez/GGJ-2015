@echo off
cd images

rem pcx2snes dwarf -c16 -o128
rem pcx2snes mymap -screen -o128
rem pcx2snes ascii -c4 -o256

rem pcx2snes cutewendy -screen
rem pcx2snes cutewendy1 -screen


pcx2snes hero -c16
pcx2snes bullets -c16

rem pcx2snes title -screen

cd..