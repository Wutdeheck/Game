how to make an exe :
download msys2
install msys2
inside msys2 (specifically the ucrt app)
pacman -S mingw-w64-ucrt-x86_64-gcc
gcc Main.c -o Tornado_Game -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
done

how to make an exe in linux :
open terminal
sudo apt install mingw-w64 (For Ubuntu,Debian,Zorin,POP!_OS,and other based Ubuntu or Debian OS)
sudo vdnf install mingw64-gcc (for fedora, rhel, centos)
gcc main.c -o name.exe
if error and has raylib
gcc Main.c -o [name].exe -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
if error
sudo apt install libx11-dev libxcursor-dev libxrandr-dev libxinerama-dev libxi-dev libxxf86vm-dev
sudo dnf install libX11-devel libXcursor-devel libXrandr-devel libXinerama-devel libXi-devel libXxf86vm-devel

how to make an appimage :
download appimagetool (idk what architecture, depends on yo system (i use arch btw, x86 or x86_64)
open terminal
im out, i hate typign
