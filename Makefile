PROJECT = runes-of-cmd
SRC_DIR = src
RUNE_DIR = rune-types
OBJ_DIR = obj

MKDIR = mkdir -p

# ALL CPP IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/$(RUNE_DIR)*.cpp)

# ALL HEADER FILES
H_FILES = $(wildcard $(SRC_DIR)/*.h) $(wildcard $(SRC_DIR)/*.hpp)


# --- Compiler Settings ---
CXX = g++
CPPVERSION = -std=c++17
CXXFLAGS = -Wall -Wextra -g $(CPPVERSION)

ifeq ($(shell echo "Windows"), "Windows")
	TARGET = $(PROJECT).exe
else
	TARGET = $(PROJECT)
endif

# --- SFML Libraries ---
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# --- Derived Variables ---
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))


# --- Default rule ---
all: $(TARGET)
	@echo "** Building the game"
	g++ -o $(TARGET) $(OBJECTS) $(LIBS)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(LIBS)


# --- Compile rule ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(H_FILES)
	$(MKDIR) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Run target ---
run: $(TARGET)
	./$(TARGET)