CXX := c++
SRC := src
BLD := build
OBJ := $(BLD)/obj
SOURCES = $(wildcard $(SRC)/*.cpp)
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SOURCES))
#BIN := $(BLD)/gap
BIN := gap.x

$(BIN): $(OBJECTS)
	$(CXX) -o $@ $^

$(OBJ)/%.o: $(SRC)/%.cpp
	@mkdir -p $(OBJ)
	$(CXX) -o $@ -c $<

clean:
	$(RM) -r $(BLD)
	$(RM) $(BIN)
