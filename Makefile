LIBS= -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SRC_FILES = src/main.cpp src/Player.cpp src/Creature.cpp src/Rune.cpp src/Compiler.cpp
OBJECTS = $(SRC_FILES:.cpp=.o)
PROJECT = runes-of-cmd
TARGET = $(PROJECT).exe


all: $(TARGET)
		@echo "** Building the game"
		$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

run: $(TARGET)
		./$(TARGET)
