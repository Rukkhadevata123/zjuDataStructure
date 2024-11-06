#include <iostream>
#include <string>

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == 'e';
}

size_t findRightOperandEnd(const std::string& expression, size_t start) {
    size_t i = start;

    // 检查是否为运算符，且其后接 "("，找到闭括号位置
    if (isOperator(expression[i])) {
        if (expression[i + 1] == '(') {
            int openParens = 1;
            i += 2;
            while (i < expression.size() && openParens > 0) {
                if (expression[i] == '(') openParens++;
                else if (expression[i] == ')') openParens--;
                i++;
            }
            return i;
        } else if (isOperator(expression[i + 1])) {
            return findRightOperandEnd(expression, i + 1);
        }
        i++;  // 跳过以检查后面的数
    }

    // 遍历操作数，可能包含小数点
    while (i < expression.size() && (std::isdigit(expression[i]) || expression[i] == '.')) {
        i++;
    }

    return i;
}

int main() {
    std::string expression = "-(3+4)*-7((7-))";
    size_t i = 6;
    size_t rightOperandEnd = findRightOperandEnd(expression, i);

    std::cout << rightOperandEnd << std::endl;
}