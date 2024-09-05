CXX = g++
CXXFLAGS = -Wall -g

TARGET = hello-isar

all: $(TARGET)

$(TARGET): main.o
    $(CXX) $(CXXFLAGS) -o $(TARGET) main.o

main.o: main.cpp
    $(CXX) $(CXXFLAGS) -c main.cpp

clean:
    rm -f *.o $(TARGET)
