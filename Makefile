build:
	g++ -w -std=c++14 -Wfatal-errors \
	main.cpp src/*.cpp src/gameObjects/*.cpp src/gameObjects/buffs/*.cpp src/states/*.cpp \
	-o game.exe \
	-I"C:\mingw_dev_lib\include" \
	-L"C:\mingw_dev_lib\lib" \
	-lmingw32 \
	-lSDL2main \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2;

clean:
	rm ./game.exe;

run:
	./game.exe;
