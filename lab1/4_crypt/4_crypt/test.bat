@echo off

set PROGRAM="%~1"
set OUTPUT="%TEMP%/output.bin"
set TEMPOUTPUT="%TEMP%/tempOutput.bin"

rem no params
%PROGRAM% > nul
if NOT ERRORLEVEL 1 goto err

rem simple test + reversed
%PROGRAM% crypt tests\simple-msg.bin %OUTPUT% 200
if ERRORLEVEL 1 goto err
%PROGRAM% decrypt %OUTPUT% %TEMPOUTPUT% 200
if ERRORLEVEL 1 goto err
fc.exe tests\simple-msg.bin %TEMPOUTPUT% > nul
if ERRORLEVEL 1 goto err

rem complicated test + reversed
%PROGRAM% crypt tests\complicated-book.txt %OUTPUT% 25
%PROGRAM% decrypt %OUTPUT% %TEMPOUTPUT% 25
fc.exe tests\complicated-book.txt %TEMPOUTPUT% > nul
if ERRORLEVEL 1 goto err

rem wrong key interval
%PROGRAM% crypt tests\wrong-key-interval.txt %OUTPUT% 256 > %TEMPOUTPUT%
fc.exe tests\wrong-key-interval-output.txt %TEMPOUTPUT% > nul
if ERRORLEVEL 1 goto err

rem wrong key interval
%PROGRAM% crypt tests\wrong-key-interval.txt %OUTPUT% -1 > %TEMPOUTPUT%
fc.exe tests\wrong-key-interval-output.txt %TEMPOUTPUT% > nul
if ERRORLEVEL 1 goto err

rem wrong crypt mode
%PROGRAM% necrypt tests\wrong-crypt-mode.txt %OUTPUT% 200 > %TEMPOUTPUT%
fc.exe tests\wrong-crypt-mode-output.txt %TEMPOUTPUT% > nul
if ERRORLEVEL 1 goto err



echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1
