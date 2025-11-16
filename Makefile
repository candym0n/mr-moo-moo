.SILENT:

CC				= g++

BIN_DIR         = bin
SRC_DIR         = src
INC_DIR         = inc

SOURCES         = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS 		= $(subst $(SRC_DIR)/,$(BIN_DIR)/,$(SOURCES:.cpp=.o))

SDLINC          = -I$(SDL_PATH)/base/include -I$(SDL_PATH)/image/include
SDLLIB          = -L$(SDL_PATH)/base/lib     -L$(SDL_PATH)/image/lib -lSDL3_image -lSDL3

CFLAGS          = -g -Wall -fdiagnostics-color=always -I$(INC_DIR) $(SDLINC)
LDFLAGS         = $(SDLLIB) -mconsole

TARGET			= build/mrmoomoo.scr

# Build the target executable
$(TARGET): $(OBJECTS)
	@echo Linking...
	$(CC) $^ -o $@ $(LDFLAGS)

# Compile all the source files
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo Compiling $<
	$(CC) -c $< -o $@ $(CFLAGS)

# DESTROY EVERYTHING
clean:
	rm $(BIN_DIR)/*

# Test run
test:
	cd build
	./$(TARGET) /s
	cd ..
