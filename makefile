CXXFLAGS += -std=c++11 -Wall -Wextra -pedantic-errors
CPPFLAGS += 

SOURCES := $(shell find . -name '*.cpp')

HEADERS := $(shell find . -name '*.h')

OUTPUT := Horcrux

all: $(OUTPUT)

$(OUTPUT): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(OUTPUT) $(SOURCES)

clean:
	$(RM) $(OUTPUT)