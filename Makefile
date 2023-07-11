

EXE = Ash
CC=g++
CFLAGS= -std=c++17 -w 
LIBS = -lglfw -lGL -lGLEW -lGLU

# fullFlags= -Wall -Wpedantic -Wextra -std=gnu17 -lglfw -lGL -lGLEW

SOURCE_DIR = src
# SOURCES = $(SOURCE_DIR)/main.cpp
SOURCES = $(SOURCE_DIR)/*.cpp
BININT = bin-int
BIN = bin
OBJS = $(addsuffix .o, $(basename $(notdir $(wildcard $(SOURCE_DIR)/*.cpp))))


default:
	make all

%.o:$(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $(BININT)/$@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CC) -o  $(BIN)/$@ $(addprefix $(BININT)/, $^) $(CFLAGS) $(LIBS)

clean:
	rm -f $(BIN)/$(EXE)
	rm -f $(BININT)/*.o
	rm -f *.o
	rm -f $(SOURCE_DIR)/*.o

run: $(EXE)
	$(BIN)/$(EXE)


echoTest:
	@echo $(OBJS)

