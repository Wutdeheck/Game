how to make an exe :
download msys2
install msys2
inside msys2 (specifically the ucrt app)
pacman -S mingw-w64-ucrt-x86_64-gcc
gcc main.c -o myprogram.exe
done

how to make an exe in linux :
open terminal
sudo apt install mingw-w64 (For Ubuntu,Debian,Zorin,POP!_OS,and other based Ubuntu or Debian OS)
sudo vdnf install mingw64-gcc (for fedora, rhel, centos)
x86_64-w64-mingw32-gcc main.c -o myprogram.exe

how to make an appimage :
download appimagetool (idk what architecture, depends on yo system (i use arch btw, x86 or x86_64)
open terminal
im out, i hate typign
