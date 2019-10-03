@echo off
	FOR /L %%x IN (0,1,99) DO CALL :testing_function %%x
	
	
:testing_function
	pracownia_3.exe<test%~1.in>test.out
	FC test.out test%~1.out > nul
	IF errorlevel 1 (
		echo %~1
	)