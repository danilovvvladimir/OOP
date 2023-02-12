@echo off

set PROGRAM="%~1"
set OUTPUT="%TEMP%/output.txt"

rem no params
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem wrong notation
%PROGRAM% 100 2 10 > %OUTPUT%
fc.exe tests\wrong-notation-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem wrong symbols
%PROGRAM% 10 2 -?s2 > %OUTPUT%
fc.exe tests\wrong-symbols-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem simple test
%PROGRAM% 2 36 100011 > %OUTPUT%
fc.exe tests\100011-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err


rem simple test
%PROGRAM% 36 10 ZZZ > %OUTPUT%
fc.exe tests\ZZZ-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem maxint
%PROGRAM% 10 2 2147483647 > %OUTPUT%
fc.exe tests\maxint-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem maxint overflow
%PROGRAM% 10 2 2147483648 > %OUTPUT%
fc.exe tests\maxint-overflow-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem minint
%PROGRAM% 10 2 -2147483648 > %OUTPUT%
fc.exe tests\minint-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem minint overflow
%PROGRAM% 10 2 -2147483649 > %OUTPUT%
fc.exe tests\minint-overflow-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err



echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1