CC := g++

SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin # or . if you want it in the current directory

EXE := $(BIN_DIR)/waveC8
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# -I is a preprocessor flag, not a compiler flag
# The -MMD -MP flags are used to generate the header dependencies automatically
CPPFLAGS := -Iinclude -MMD -MP 
# some warnings about bad code		
CFLAGS   := -Wall 
# Include paths
INCLUDES := -IC:\msys64\mingw64\include\SDL2
# -L is a linker flag
LDFLAGS  := -Llib
# Left empty if no libs are needed
LDLIBS   := -lm -lmingw32 -lSDL2main -lSDL2

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

# The dash is used to silence errors if the files don't exist yet
-include $(OBJ:.o=.d)
