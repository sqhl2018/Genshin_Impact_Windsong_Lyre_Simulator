defines=SFML_STATIC
includepath=SFML/include
libdir=SFML/lib_static/
libs= -lsfml-window-s -lsfml-graphics-s -lsfml-system-s -lsfml-audio-s -lsfml-system-s -lsfml-main -lfreetype -lopenal32 -lflac -lvorbisenc -lvorbisfile  -lvorbis -logg -lgdi32 -lwinmm -lopengl32 
qin_static.exe:src/main.cpp src/game.cpp src/game.h tmp/icon.o res/res.o src/res.cpp
	g++ -O3 src/main.cpp src/game.cpp res/res.o src/res.cpp tmp/icon.o lib/imm32.lib -L $(libdir)  $(libs) -I $(includepath) -D $(defines) -o qin_static.exe -mwindows
tmp/icon.o:src/icon.ico src/icon.rc
	windres src/icon.rc tmp/icon.o