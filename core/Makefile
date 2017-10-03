SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)
OBJECTS = $(SOURCES:%.cpp=%.o)
TARGET 	= closest
FLAGS	= -std=c++11 -O2

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(FLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp $(HEADERS)
	$(CXX) $(FLAGS) -c $< -o $@

clean:
	rm -rf *.o *~ $(TARGET)
