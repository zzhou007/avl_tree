# the compiler: gcc for C program, define as g++ for C++
CC11 = g++ -std=c++11
	
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall
	
# the build target executable:
TARGET = testtree
HEAD = avltree
INPPUT =
	
all:$(TARGET)
	
$(TARGET): $(TARGET).cpp $(HEAD).h
	$(CC11) $(CFLAGS) -o $(TARGET) $(TARGET).cpp
clean:
	$(RM) $(TARGET)
