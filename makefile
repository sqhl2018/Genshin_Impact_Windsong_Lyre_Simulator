defines=-D SFML_STATIC -D AL_LIBTYPE_STATIC -D IMM_COMPILE
includepath=SFML/include
libdir=SFML/lib_static/
libsfml=-lsfml-window-s -lsfml-graphics-s -lsfml-system-s -lsfml-audio-s -lsfml-system-s -lsfml-main 
libsfml_dep=-lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile  -lvorbis -logg -lgdi32 -lwinmm -lopengl32 -limm32 -lole32 -loleaut32
qin_static.exe:src/main.cpp src/game.cpp src/game.h tmp/icon.o res/res.o src/res.cpp
	g++ -static -Os src/main.cpp src/game.cpp res/res.o src/res.cpp tmp/icon.o -L $(libdir)  $(libsfml) $(libsfml_dep) -I $(includepath)  $(defines) -o qin_static.exe -mwindows
tmp/icon.o:src/icon.ico src/icon.rc
	windres src/icon.rc tmp/icon.o