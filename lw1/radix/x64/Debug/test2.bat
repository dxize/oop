@echo off
chcp 1251 > nul

setlocal

set PROGRAM=radix.exe

echo �������� ����� 1: 16 10 1F
echo ��������: 31
%PROGRAM% "16" "10" "1F"
echo.

echo �������� ����� 2: 10 2 -5
echo ��������: -101
%PROGRAM% "10" "2" "-5"
echo.

echo �������� ����� 3: 10 2 0
echo ��������: 0
%PROGRAM% "10" "2" "0"
echo.

echo �������� ����� 4: 10
echo ��������: "ERROR"
%PROGRAM% "10"
echo.

echo �������� ����� 5: 10 2
echo ��������: "ERROR"
%PROGRAM% "10" "2"
echo.

echo �������� ����� 6:
echo ��������: "ERROR"
%PROGRAM% 
echo.

echo �������� ����� 7:
echo ��������: "ERROR"
%PROGRAM% "p" "g" "10"
echo.

echo �������� ����� 8: 
echo ��������: "ERROR"
%PROGRAM% "10" "2" "n"
echo.

echo �������� ����� 9: 
echo ��������: "ERROR"
%PROGRAM% "1" "2" "0"
echo.

echo �������� ����� 10: 
echo ��������: "ERROR"
%PROGRAM% "40" "2" "1"
echo.

echo �������� ����� 11: 
echo ��������: "ERROR"
%PROGRAM% "10" "2" "1F"
echo.

echo �������� ����� 12: 
echo ��������: 1111111111111111111111111111111 
%PROGRAM% "10" "2" "2147483647"
echo.

endlocal

pause

//�������� �������� �� ������� - 1 � ������� + 1