SOURCE_DIR = src
IMGUI_DIR = $(SOURCE_DIR)/imgui
SOURCES = $(SOURCE_DIR)/*.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
BININT = bin-int
BIN = bin
OBJS = $(addprefix $(BININT)/, $(addsuffix .o, $(basename $(notdir $(wildcard $(SOURCES))))))


EXE = Ash
CC=g++
CFLAGS= -std=c++17 -w -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
# fullFlags= -Wall -Wpedantic -Wextra -std=gnu17 -lglfw -lGL -lGLEW
LIBS = -lglfw -lGL -lGLEW -lGLU -ldl


default:
	make all

$(BININT)/%.o:$(SOURCE_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


$(BININT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CC) $(CFLAGS) -c -o $@ $<


$(BININT)/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

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

