@echo off

set PROGRAM="%~1"
set OUTPUT="%TEMP%"


%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

%PROGRAM% tests\aa.txt "%TEMP%\output-aa.txt" aa a
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output-aa.txt" tests\aa-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% tests\12312312345.txt "%TEMP%\output-12312312345.txt" 1231234 ITWORKS
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output-12312312345.txt" tests\12312312345-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% tests\empty.txt "%TEMP%\output-empty.txt" 1231234 ITWORKS
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output-empty.txt" tests\empty-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% tests\multi.txt "%TEMP%\output-multi.txt" meow GAV
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output-multi.txt" tests\multi-correct-output.txt > nul
if ERRORLEVEL 1 goto err

%PROGRAM% tests\lengthzero.txt "%TEMP%\output-lengthzero.txt" "" ESENIN
if ERRORLEVEL 1 goto err
fc.exe "%TEMP%\output-lengthzero.txt" tests\lengthzero-correct-output.txt > nul
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1