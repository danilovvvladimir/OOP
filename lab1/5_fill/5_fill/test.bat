@echo off

set PROGRAM="%~1"
set OUTPUT="%TEMP%"

rem no params
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem empty map
%PROGRAM% tests\empty.txt "%TEMP%\empty-temp-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\empty-temp-out.txt" tests\empty-output.txt > nul
if ERRORLEVEL 1 goto err

rem max
%PROGRAM% tests\max.txt "%TEMP%\max-temp-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\max-temp-out.txt" tests\max-output.txt > nul
if ERRORLEVEL 1 goto err

rem max bordered
%PROGRAM% tests\max-bordered.txt "%TEMP%\max-bordered-temp-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\max-bordered-temp-out.txt" tests\max-bordered-output.txt > nul
if ERRORLEVEL 1 goto err

rem multicenters
%PROGRAM% tests\multicenters.txt "%TEMP%\multicenters-temp-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\multicenters-temp-out.txt" tests\multicenters-output.txt > nul
if ERRORLEVEL 1 goto err

rem out of range
%PROGRAM% tests\out-of-range.txt "%TEMP%\out-of-range-temp-out.txt"
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\out-of-range-temp-out.txt" tests\out-of-range-output.txt > nul
if ERRORLEVEL 1 goto err

rem secured file
%PROGRAM% tests\secured-file.txt tests\secured-file-output.txt 
if NOT ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1