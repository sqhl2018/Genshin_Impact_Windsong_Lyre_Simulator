defines=-D SFML_STATIC -D AL_LIBTYPE_STATIC -D DISABLE_INPUTMETHOD -D ROUND_RECT_WINDOW
includepath=SFML/include
libdir=SFML/lib_static/
libsfml=-lsfml-window-s -lsfml-graphics-s -lsfml-system-s -lsfml-audio-s -lsfml-system-s -lsfml-main 
libsfml_dep=-lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile  -lvorbis -logg -lgdi32 -lwinmm -lopengl32 -limm32 -lole32 -loleaut32 -ldwmapi
no_shell_window=-mwindows
WindsongLyre.exe:src/main.cpp src/game.cpp src/game.h tmp/icon.o tmp/res.o src/res.cpp FORCE_UPDATE
	g++ -static -Os src/main.cpp src/game.cpp tmp/res.o src/res.cpp tmp/icon.o -L $(libdir)  $(libsfml) $(libsfml_dep) -I $(includepath)  $(defines) -o WindsongLyre.exe -mwindows
tmp/icon.o:src/icon.ico src/icon.rc
	windres src/icon.rc tmp/icon.o
tmp/res.o:tmp/res_arr.cpp
	gcc -c tmp/res_arr.cpp -o tmp/res.o
tmp/res_arr.cpp:res/*
	./resProcessor.exe
release:WindsongLyre.exe
	upx WindsongLyre.exe
FORCE_UPDATE:
upx:WindsongLyre.exe
	upx WindsongLyre.exe
