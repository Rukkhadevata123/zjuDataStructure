# 定义编译器
CXX = g++

# 编译选项
CXXFLAGS = -Wall -g

# 源文件
SRC = hello.cpp

# 目标文件
TARGET = hello

# 编译规则
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# 清理规则
clean:
	rm -f $(TARGET)