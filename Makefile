EXEC = trabalhocg

all: 
	g++ -o $(EXEC) *.cpp tinyxml2/*.cpp -I./tinyxml2 -lGL -lGLU -lglut

run:
	./$(EXEC) arena_teste.svg
clean:
	rm -f $(EXEC)
	rm -f tinyxml2/*.o
