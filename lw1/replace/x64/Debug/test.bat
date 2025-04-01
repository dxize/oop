@echo off
chcp 1251 > nul

setlocal

set PROGRAM=replace.exe
set INPUT_FILE=input1.txt
set OUTPUT_FILE=output1.txt
set INPUT_FILE_2=input2.txt
set OUTPUT_FILE_2=output2.txt
set INPUT_FILE_3=input3.txt
set OUTPUT_FILE_3=output3.txt

%PROGRAM% "%INPUT_FILE%" "%OUTPUT_FILE%" "ma" "mama"

echo ���� 1: ma mama mama delala pelmeni
echo ��������: mamamama delala pelmeni
type "%OUTPUT_FILE%"
echo.


%PROGRAM% "%INPUT_FILE_2%" "%OUTPUT_FILE_2%" "1231234" "XYZ"

echo T��� 2: 1231234 XYZ 12312312345
echo ��������: 123XYZ5
type "%OUTPUT_FILE_2%"
echo.

%PROGRAM% "%INPUT_FILE_3%" "%OUTPUT_FILE_3%" "" "tam"

echo ���� 3: "" tam tut text
echo ��������: tut text
type "%OUTPUT_FILE_3%"
echo.

echo ���� 4: EOLN hello EOF
echo ��������: ERROR
echo hello | %PROGRAM%
echo.

endlocal

echo ���� 5: ���������� �� ����������
echo ��������: 
echo "1) Usage: replace.exe <input file> <output file> <search string> <replace string>"    
echo "2) Usage: replace.exe -h" 
echo "3) Use stdin."
echo ���������:
replace.exe -h
 
echo ���� 6: ���������� ���������� ���������� (3)
echo ��������: ERROR
replace.exe "1" "2" 

echo ���� 7: ���������� ���������� ���������� (4)
echo ��������: ERROR
replace.exe "1" "2" "3"

echo ���� 8: ������������ �������� �������� �����
echo ��������: ERROR
replace.exe "%INPUT_FILE%" "2" "3" "4"

echo T��� 9: ������������ �������� ��������� �����
echo ��������: ERROR
replace.exe "1" "%OUTPUT_FILE_%" "2" "3"

pause
