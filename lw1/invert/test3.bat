@echo off
chcp 1251 > nul

setlocal

set PROGRAM=invert.exe
set TEST1_FILE=test1.txt
set TEST2_FILE=test2.txt
set INVALID1_FILE=invalid1.txt
set INVALID2_FILE=invalid2.txt
set ZERO_FILE=zero.txt
set EMPTY_FILE=empty.txt


echo ���� 1: 
echo 1   2   3
echo 0   1   4
echo 5   6   0
echo ��������: 
echo.
echo -24.000	18.000	5.000
echo 20.000	-15.000	-4.000
echo -5.000	4.000	1.000
%PROGRAM% "%TEST1_FILE%"
echo.


echo ���� 2: 
echo 1   2   3
echo 2   4   6
echo 1   2   3
echo ��������: 
echo.
echo -24.000	18.000	5.000
echo 20.000	-15.000	-4.000
echo -5.000	4.000	1.000
%PROGRAM% "%TEST2_FILE%"
echo.


echo ���� 3: 
echo 1   2   a
echo 2   4   6
echo 1   2   3
echo ��������: 
echo.
echo Invalid matrix
%PROGRAM% "%INVALID1_FILE%"
echo.

echo ���� 4: 
echo 1   2   3
echo 0   1   4
echo ��������: 
echo.
echo Invalid matrix format
%PROGRAM% "%INVALID2_FILE%"
echo.

echo ���� 5: 
echo 0   0   0
echo 0   0   0
echo 0   0   0
echo ��������: 
echo.
%PROGRAM% "%ZERO_FILE%"
echo.

echo ���� 6:
echo ��������: 
echo  Invalid matrix format
echo.
%PROGRAM% "%EMPTY_FILE%"
echo.

endlocal

echo ���� 7: ���������� �� ����������
echo ��������: 
echo "1) For manual entry, enter only the name of the executable file into the command line"
echo.
echo "2) If there is a file with a pre-prepared graph, then enter the name of the executable file in the console and, separated by a space, the name of the file with the input data"
echo.
echo.
echo "!!!!The coefficients of the input matrix are arranged in three elements in each row (3*3) and are separated by a tab character!!!!"
echo.
echo ���������:
invert.exe -h
 
echo ���� 8: ���������� ���������� ���������� (3)
echo ��������: 
echo. 
echo ERROR!\nEnter -h for help or check if the parameters you entered are correct.
echo.
echo ���������:
invert.exe "1" "2" 

pause
