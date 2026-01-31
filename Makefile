CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

TARGET = password_manager
OBJS = main.o PasswordUtils.o HashTable.o

TEST_TARGET = tests
TEST_OBJS = tests.o PasswordUtils.o HashTable.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp PasswordUtils.hpp HashTable.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

PasswordUtils.o: PasswordUtils.cpp PasswordUtils.hpp
	$(CXX) $(CXXFLAGS) -c PasswordUtils.cpp

HashTable.o: HashTable.cpp HashTable.hpp
	$(CXX) $(CXXFLAGS) -c HashTable.cpp

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) -o $(TEST_TARGET) $(TEST_OBJS)

tests.o: tests.cpp PasswordUtils.hpp HashTable.hpp
	$(CXX) $(CXXFLAGS) -c tests.cpp

data: $(TARGET)
	./$(TARGET)

test: data $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f *.o $(TARGET) $(TEST_TARGET)

run: $(TARGET)
	./$(TARGET)