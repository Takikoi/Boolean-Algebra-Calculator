all: compile run

compile:
	g++ ../src/*.cpp -o Main.exe -w -I ../include/ -I ../include/ProjectHPP -L ../lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

debug:
	g++ ../src/*.cpp -g -o Main.exe -I ../include/ -I ../include/ProjectHPP -L ../lib/ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

run:
	./Main.exe