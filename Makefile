# Output 'game' so grader can run: make && ./game
GAME = game
GAME_FILES = src/main.cpp src/inscryption.cpp $(wildcard src/*/*.cpp)


CXXFLAGS = -Wall -Wextra -O0 -g3 -fno-omit-frame-pointer -D_GLIBXX_DEBUG


game: $(GAME_FILES)
	g++ $(CXXFLAGS) $(GAME_FILES) -o $(GAME)

clean:
	rm -f $(GAME)
	rm -rf *.dSYM

