# Condition Variable Demo Makefile
CXX		 = g++
CXXFLAGS = -Wall -std=c++17
TARGET	 = source
SRC		 = source.c

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)