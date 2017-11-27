SRC=TowerDefense.c
BIN=TowerDefense

$(BIN): $(SRC) fonction.o
	gcc $(SRC) fonction.o -Wall -g -std=c99 `sdl-config --cflags --libs` -lSDL_ttf -lm -o $(BIN)

fonction.o: fonction.c 
	gcc -o fonction.o -c fonction.c -g -W -Wall -std=c99 `sdl-config --cflags --libs`

clean:
	rm -f $(BIN) *.o
