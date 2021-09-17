resProcessor.exe:src/main.cpp tmp/icon.o
	gcc src/main.cpp  tmp/icon.o -o resProcessor.exe -lstdc++
tmp/icon.o:src/icon.ico src/icon.rc
	windres src/icon.rc tmp/icon.o