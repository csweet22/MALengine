SOURCE_DIR = src
IMGUI_DIR = $(SOURCE_DIR)/imgui
SOURCES = $(SOURCE_DIR)/*.cpp
SOURCES += $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
SOURCES += $(IMGUI_DIR)/imgui_impl_glfw.cpp $(IMGUI_DIR)/imgui_impl_opengl3.cpp
BININT = bin-int
BIN = bin
OBJS = $(addprefix $(BININT)/, $(addsuffix .o, $(basename $(notdir $(wildcard $(SOURCES))))))
DEPENDS = $(addprefix $(BININT)/, $(addsuffix .d, $(basename $(notdir $(wildcard $(SOURCES))))))


EXE = Ash
CXX=g++
CXXFLAGS= -std=c++17 -w -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends
# fullFlags= -Wall -Wpedantic -Wextra -std=gnu17 -lglfw -lGL -lGLEW
LIBS = -lglfw -lGL -lGLEW -lGLU -ldl


default:
	make all

-include $(BININT)/$(DEPENDS)

$(BININT)/%.o:$(SOURCE_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $< -MMD -MP 


$(BININT)/%.o:$(IMGUI_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<


$(BININT)/%.o:$(IMGUI_DIR)/backends/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $(BIN)/$@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(BININT)/*.d $(BININT)/*.o

run: $(EXE)
	$(BIN)/$(EXE)


test:
	@echo sources $(SOURCES)
	@echo \|
	@echo objects $(OBJS)
	@echo \|
	@echo depends $(DEPENDS)

