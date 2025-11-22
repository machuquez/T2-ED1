@echo off
echo Compilando programa ED1...

REM Limpar compilações anteriores
if exist "obj\*.o" del /Q "obj\*.o"
if exist "bin\*.exe" del /Q "bin\*.exe"

REM Criar pastas se não existirem
if not exist "obj" mkdir "obj"
if not exist "bin" mkdir "bin"

REM Compilar todos os .c da pasta src
gcc -c src\*.c -I include
move *.o obj\ >nul 2>&1

REM Compilar main e ligar com objetos
gcc apps\main.c obj\*.o -I include -o bin\programa.exe -lm

echo.
echo Compilacao concluida com sucesso!
echo Executando programa...
echo.
bin\programa.exe

pause