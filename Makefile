CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

TARGET = password_manager
OBJS = main.o PasswordUtils.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp PasswordUtils.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

PasswordUtils.o: PasswordUtils.cpp PasswordUtils.hpp
	$(CXX) $(CXXFLAGS) -c PasswordUtils.cpp

clean:
	rm -f $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)