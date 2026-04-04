PROJECT = runes-of-cmd
SRC_DIR = src
RUNE_DIR = rune-types
OBJ_DIR = obj
BIN_DIR = bin

ifeq ($(shell echo "Windows"), "Windows")
    RM      := del /f /q
    RMDIR   := rd /s /q
    MKDIR   := mkdir
    CP      := copy /y
    DIR_SEP := /  # Use forward slashes (Windows supports this)
    EXE_EXT := .exe
else
    RM      := rm -f
    RMDIR   := rm -rf
    MKDIR   := mkdir -p
    CP      := cp
    DIR_SEP := /
    EXE_EXT :=
endif

# ALL CPP IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = $(wildcard $(SRC_DIR)$(DIR_SEP)*.cpp) $(wildcard $(SRC_DIR)$(DIR_SEP)$(RUNE_DIR)*.cpp)

# ALL HEADER FILES
H_FILES = $(wildcard $(SRC_DIR)$(DIR_SEP)*.h) $(wildcard $(SRC_DIR)$(DIR_SEP)*.hpp)


# --- Compiler Settings ---
CXX = g++
CPPVERSION = -std=c++17
CXXFLAGS = -Wall -Wextra -g $(CPPVERSION)

TARGET =  $(BIN_DIR)$(DIR_SEP)$(PROJECT)$(EXE_EXT)

# --- SFML Libraries ---
LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# --- Derived Variables ---
OBJECTS = $(patsubst $(SRC_DIR)$(DIR_SEP)%.cpp,$(OBJ_DIR)$(DIR_SEP)%.o,$(SRC_FILES))


# --- Default rule ---
all: $(TARGET)
	@echo "** Building the game"
	g++ -o $(TARGET) $(OBJECTS) $(LIBS)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $^ $(LIBS)


# --- Compile rule ---
$(OBJ_DIR)$(DIR_SEP)%.o: $(SRC_DIR)$(DIR_SEP)%.cpp $(H_FILES)
	$(MKDIR) $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# --- Run target ---
run: $(TARGET)
	.$(DIR_SEP)$(TARGET)