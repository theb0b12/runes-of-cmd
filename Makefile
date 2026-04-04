PROJECT = runes-of-cmd
SRC_DIR = src
RUNE_DIR = rune-types
OBJ_DIR = obj
BIN_DIR = bin

#ifeq ($(shell echo "Windows"), "Windows")
    RM      := del /f /q
    RMDIR   := rd /s /q
    MKDIR   := mkdir
    CP      := copy /y
    EXE_EXT := .exe
#  else
#      RM      := rm -f
#      RMDIR   := rm -rf
#      MKDIR   := mkdir -p
#      CP      := cp
#      DIR_SEP := /
#      EXE_EXT :=
#  endif

# ALL CPP IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = $(wildcard src/*.cpp) 

# ALL HEADER FILES
H_FILES = $(wildcard src/*.h) $(wildcard src/*.hpp)


# --- Compiler Settings ---
CXX = g++
CPPVERSION = -std=c++17
CXXFLAGS = -Wall -Wextra -g $(CPPVERSION)

TARGET =  $(BIN_DIR)/$(PROJECT)$(EXE_EXT)

# --- SFML Libraries ---
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# --- Derived Variables ---
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))


# --- Default rule ---
all: $(TARGET)
	@echo "** Building the game"

$(TARGET): $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)


# --- Compile rule ---
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(H_FILES)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Run target ---
run: $(TARGET)
	./$(TARGET)