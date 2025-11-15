.SILENT:

CC				= g++

BIN_DIR         = bin
SRC_DIR         = src
INC_DIR         = inc

SOURCES         = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS 		= $(subst $(SRC_DIR)/,$(BIN_DIR)/,$(SOURCES:.cpp=.o))

SDLINC          = -I$(SDL_PATH)/include
SDLLIB          = -L$(SDL_PATH)/lib -lSDL3

CFLAGS          = -g -Wall -fdiagnostics-color=always -I$(INC_DIR) $(SDLINC)
LDFLAGS         = $(SDLLIB) -mwindows

TARGET			= build/mrmoomoo.scr

all: $(TARGET)
	$(MAKE) $(TARGET)

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
	rmdir /s /q $(BIN_DIR)
	@mkdir bin

# Test run
test:
	./$(TARGET) /s
