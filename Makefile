CC = g++
CPPFLAGS = -Wall
OPT = -O3
OBJ = obj/main.o obj/text.o obj/parsing.o

main: $(OBJ)
	$(CC) $(OPT) $^ -o $@

obj/main.o: main.cpp
	$(CC) -c $(CPPFLAGS) $< -o obj/main.o

obj/%.o: src/%.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

clean:
	rm -f obj/*.o


.PHONY: clean