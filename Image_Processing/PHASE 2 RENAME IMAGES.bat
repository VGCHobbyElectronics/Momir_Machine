@echo off
setlocal EnableDelayedExpansion

set filename=FileTitle
set suffix=10000
for /F "delims=" %%i in ('dir /B /S *.jpg') do (
   set /A suffix+=1
   ren "%%i" "!suffix:~1!.jpg"
)