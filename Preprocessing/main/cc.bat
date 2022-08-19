cls
REM @ECHO OFF 
if exist *.exe del *.exe
@ECHO ====== START : compile  ======
for %%f in (*.c) do gcc -c -Wall -g %%f

@ECHO ====== START : link  ======
gcc -o chek.exe chek.o
gcc -o detect.exe detect.o
gcc -o extract.exe extract.o
gcc -o image.exe image.o

if exist *.o del *.o
@ECHO ====== FINISH  ======
