#ifndef EXPRESSION_EVALUATOR_H
#define EXPRESSION_EVALUATOR_H

#include <string>
#include <vector>
#include <stack>
#include <stdexcept>
#include <cmath>

class ExpressionEvaluator {
public:
    // 检测是否包含非法字符
    static bool hasInvalidCharacters(const std::string& expression);

    // 检测括号是否匹配
    static bool areParenthesesBalanced(const std::string& expression);

    // 检测是否包含多余的小数点
    static bool hasExtraDecimalPoint(const std::string& expression);

    // 检测连续运算符
    static bool hasInvalidOperatorSequence(const std::string& expression);

    // 删除空格
    static std::string removeSpaces(const std::string& expression);

    // 添加括号
    static std::string addParentheses(const std::string& expression);

    // 寻找右操作数
    static size_t findRightOperandEnd(const std::string& expression, size_t start);

    // 预处理
    static std::string preprocessExpression(const std::string& expression);

    // 拆分表达式
    static std::vector<std::string> tokenizeExpression(const std::string& expression);

    // 中缀表达式转后缀表达式
    static std::string infixToPostfix(const std::string& expression);

    // 计算后缀表达式
    static double evaluatePostfix(const std::string& postfixExpression);


private:
    // 辅助函数
    static int getPrecedence(char op) {
        if (op == '+' || op == '-') return 1;
        if (op == '*' || op == '/') return 2;
        if (op == 'e') return 3;
        return 0;
    }

    static bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == 'e';
    }

    static double applyOperation(double a, double b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) throw std::runtime_error("Division by zero");
                return a / b;
            case 'e': return a * std::pow(10, b);
            default: throw std::runtime_error("Invalid operator");
        }
    }
};

#endif // EXPRESSION_EVALUATOR_H