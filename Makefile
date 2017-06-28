all: emu clean


keyboard.o: src/keyboard/keyboard.cpp
	g++ -std=c++11 -c -o keyboard.o src/keyboard/keyboard.cpp

cpu.o: src/cpu/cpuBase.cpp
	g++ -std=c++11 -c -o cpu.o src/cpu/cpuBase.cpp

chip8.o: src/chip8/chip8.cpp
	g++ -std=c++11 -c -o chip8.o src/chip8/chip8.cpp

main.o: main.cpp
	g++ -std=c++11 -c -o main.o main.cpp

emu: keyboard.o cpu.o chip8.o main.o
	g++ -std=c++11 -o emu keyboard.o cpu.o chip8.o main.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

clean:      

    rm -rf *.o

