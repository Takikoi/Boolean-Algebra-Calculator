all: compile run

compile:
	g++ ../src/*.cpp -o BoolCalculator.exe -w -I ../include/ -I ../include/ProjectHPP -I ../include/Thinh -I ../include/Long -L ../lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

debug:
	g++ ../src/*.cpp -g -o Main.exe -I ../include/ -I ../include/ProjectHPP -L ../lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

run:
	./BoolCalculator.exe