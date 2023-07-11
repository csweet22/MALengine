

EXE = Ash
CC=g++
CFLAGS= -std=c++17 -w
LIBS = -lglfw -lGL -lGLEW -lGLU

# fullFlags= -Wall -Wpedantic -Wextra -std=gnu17 -lglfw -lGL -lGLEW



SOURCE_DIR = src
IMGUI_DIR = $(SOURCE_DIR)/imgui
SOURCES = $(SOURCE_DIR)/*.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp
BININT = bin-int
BIN = bin
OBJS = $(addprefix $(BININT)/, $(addsuffix .o, $(basename $(notdir $(wildcard $(SOURCES))))))

default:
	make all

$(BININT)/%.o:$(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


$(BININT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CC) -o $(BIN)/$@ $^ $(CFLAGS) $(LIBS)

clean:
	rm -f $(BIN)/$(EXE)
	rm -f $(BININT)/*.o
	rm -f *.o
	rm -f $(SOURCE_DIR)/*.o

run: $(EXE)
	$(BIN)/$(EXE)


echoTest:
	@echo sources $(SOURCES)
	@echo \|
	@echo objects $(OBJS)

