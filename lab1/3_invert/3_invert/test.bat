@echo off

set PROGRAM="%~1"
set OUTPUT="%TEMP%/output.txt"

rem no params
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem simple matrix
%PROGRAM% tests\simple-matrix.txt > %OUTPUT%
fc.exe tests\simple-matrix-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem empty matrix
%PROGRAM% tests\empty-matrix.txt > %OUTPUT%
fc.exe tests\empty-matrix-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem nullish determinant
%PROGRAM% tests\nullish-determinant.txt > %OUTPUT%
fc.exe tests\nullish-determinant-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err

rem complicated matrix
%PROGRAM% tests\complicated-matrix.txt > %OUTPUT%
fc.exe tests\complicated-matrix-output.txt %OUTPUT% > nul
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1