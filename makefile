build:
	mingw32-gcc -Wfatal-errors \
	./source/*.cpp \
	-I"include" \
	-I"C:\libsdl\include" \
	-L"C:\libsdl\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2 \
	-lSDL2_ttf \
	-lstdc++ \
	-o Swoosh.exe