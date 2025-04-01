@echo off
chcp 1251 > nul

setlocal

set PROGRAM=radix.exe

echo Проверка Теста 1: 16 10 1F
echo Ожидание: 31
%PROGRAM% "16" "10" "1F"
echo.

echo Проверка Теста 2: 10 2 -5
echo Ожидание: -101
%PROGRAM% "10" "2" "-5"
echo.

echo Проверка Теста 3: 10 2 0
echo Ожидание: 0
%PROGRAM% "10" "2" "0"
echo.

echo Проверка Теста 4: 10
echo Ожидание: "ERROR"
%PROGRAM% "10"
echo.

echo Проверка Теста 5: 10 2
echo Ожидание: "ERROR"
%PROGRAM% "10" "2"
echo.

echo Проверка Теста 6:
echo Ожидание: "ERROR"
%PROGRAM% 
echo.

echo Проверка Теста 7:
echo Ожидание: "ERROR"
%PROGRAM% "p" "g" "10"
echo.

echo Проверка Теста 8: 
echo Ожидание: "ERROR"
%PROGRAM% "10" "2" "n"
echo.

echo Проверка Теста 9: 
echo Ожидание: "ERROR"
%PROGRAM% "1" "2" "0"
echo.

echo Проверка Теста 10: 
echo Ожидание: "ERROR"
%PROGRAM% "40" "2" "1"
echo.

echo Проверка Теста 11: 
echo Ожидание: "ERROR"
%PROGRAM% "10" "2" "1F"
echo.

echo Проверка Теста 12: 
echo Ожидание: 1111111111111111111111111111111 
%PROGRAM% "10" "2" "2147483647"
echo.

endlocal

pause

//добавить проверку на интмакс - 1 и интмакс + 1