# Compiler
CC = g++

# Directories
APPNAME = Main
SRC_DIR = src
INCLUDE_DIR = include
# OPEN_GL=GL
# DEPS_DIR = deps
BIN_DIR = bin


# Compiler flags
CFLAGS = -std=c++17 -g -Wall  -I$(INCLUDE_DIR)

# Libraries
# LIBS= -L $(DEPS_DIR)/lib  -lglfw3 -lopengl32 -lgdi32
LIBS= -L -ldl -lSDL2 -lSDL2main 


# Source files
SRCSA = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*.c)


# Object files
OBJSA = $(patsubst $(SRC_DIR)/%.cpp, $(BIN_DIR)/%.o, $(SRCSA)) 


# Executable name
EXEC = main



all: $(BIN_DIR) $(EXEC)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(EXEC): $(OBJSA) $(OBJSB)
	$(CC) $(CFLAGS) -o $(BIN_DIR)/$(EXEC)  $(OBJSA) $(LIBS) 


$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@ $(LIBS) 


clean:
	@echo Cleaning file ...
	rm -r $(BIN_DIR)/*


run : $(EXEC) 
	 ./$(BIN_DIR)/main



