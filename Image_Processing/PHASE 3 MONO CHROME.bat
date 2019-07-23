@echo off
setlocal EnableDelayedExpansion

set suffix=10000
for /F "delims=" %%i in ('dir /B /S *.jpg') do (
   set /A suffix+=1
   magick convert "%%i" -resize 360x520 -monochrome "!suffix:~1!.bmp"
)