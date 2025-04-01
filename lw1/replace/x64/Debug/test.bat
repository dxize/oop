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

echo Тест 1: ma mama mama delala pelmeni
echo Ожидание: mamamama delala pelmeni
type "%OUTPUT_FILE%"
echo.


%PROGRAM% "%INPUT_FILE_2%" "%OUTPUT_FILE_2%" "1231234" "XYZ"

echo Tест 2: 1231234 XYZ 12312312345
echo Ожидание: 123XYZ5
type "%OUTPUT_FILE_2%"
echo.

%PROGRAM% "%INPUT_FILE_3%" "%OUTPUT_FILE_3%" "" "tam"

echo Тест 3: "" tam tut text
echo Ожидание: tut text
type "%OUTPUT_FILE_3%"
echo.

echo Тест 4: EOLN hello EOF
echo Ожидание: ERROR
echo hello | %PROGRAM%
echo.

endlocal

echo Тест 5: Инструкция по выполнению
echo Ожидание: 
echo "1) Usage: replace.exe <input file> <output file> <search string> <replace string>"    
echo "2) Usage: replace.exe -h" 
echo "3) Use stdin."
echo Результат:
replace.exe -h
 
echo Тест 6: Невалидное количество аргументов (3)
echo Ожидание: ERROR
replace.exe "1" "2" 

echo Тест 7: Невалидное количество аргументов (4)
echo Ожидание: ERROR
replace.exe "1" "2" "3"

echo Тест 8: Неправильное название входного файла
echo Ожидание: ERROR
replace.exe "%INPUT_FILE%" "2" "3" "4"

echo Tест 9: Неправильное название выходного файла
echo Ожидание: ERROR
replace.exe "1" "%OUTPUT_FILE_%" "2" "3"

pause
