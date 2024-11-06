#include "expression_evaluator.h"
#include <cctype>
#include <vector>
#include <sstream>

bool ExpressionEvaluator::hasInvalidCharacters(const std::string& expression) {
    // 检查是否包含非法字符（仅保留数字、运算符、小数点和括号）
    for (char c : expression) {
        if (!std::isspace(c) && !std::isdigit(c) && c != '+' && c != '-' && c != '*' && c != '/' && c != '(' && c != ')' && c != 'e' && c != '.') {
            return false;
        }
    }
    return true;
}

bool ExpressionEvaluator::areParenthesesBalanced(const std::string& expression) {
    std::stack<char> stack;

    for (char c : expression) {
        if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            if (stack.empty()) {
                return false; // 没有匹配的左括号
            }
            stack.pop();
        }
    }

    return stack.empty(); // 如果栈为空，说明所有括号都匹配
}

bool ExpressionEvaluator::hasExtraDecimalPoint(const std::string& expression) {
    bool inNumber = false;  // 是否在一个数字部分中
    bool hasDecimalPoint = false;  // 当前数字部分是否已有小数点

    for (char c : expression) {
        if (std::isdigit(c)) {
            inNumber = true;  // 开始一个新的数字部分
        } else if (c == '.') {
            if (hasDecimalPoint) {
                return true;  // 如果已经有小数点，则多余
            }
            hasDecimalPoint = true;  // 标记当前数字部分有小数点
        } else {
            // 遇到其他字符，结束当前数字部分的检查
            inNumber = false;
            hasDecimalPoint = false;
        }
    }

    return false;  // 未检测到多余小数点
}

std::string ExpressionEvaluator::removeSpaces(const std::string& expression) {
    std::string result;

    for (char c : expression) {
        if (!std::isspace(c)) {
            result += c;
        }
    }

    return result;
}

std::string ExpressionEvaluator::addParentheses(const std::string &expression) {
    std::string cleanedExpression = removeSpaces(expression);
    size_t len = cleanedExpression.length();
    std::string result;

    if (len == 0) return result;
    if (cleanedExpression[0] != '(' || cleanedExpression[len - 1] != ')') {
        result = "(" + cleanedExpression + ")";
        return result;
    }
    return cleanedExpression;
}

bool ExpressionEvaluator::hasInvalidOperatorSequence(const std::string& expression) {
    std::string cleanedExpression = addParentheses(expression);
    size_t len = cleanedExpression.length();

    // 检查连续的符号
    std::vector<std::string> invalidSequence = {
        "+*", "+/", "+)",
        "-*", "-/", "-)",
        "**", "*/", "*)",
        "/*", "//", "/)",
        "e*", "e/", "ee", "e)", "e+",
        "(*", "(/", "()",
        ")(", ").",
        ".+", ".-", ".*", "./", ".e",
        ".)", ".(", "..",
        "0(", "1(", "2(", "3(", "4(", "5(", "6(", "7(", "8(", "9(",
        ")0", ")1", ")2", ")3", ")4", ")5", ")6", ")7", ")8", ")9",
    };

    for (const std::string& seq : invalidSequence) {
        if (cleanedExpression.find(seq) != std::string::npos) {
            return true;
        }
    }

    return false;
}

size_t ExpressionEvaluator::findRightOperandEnd(const std::string& expression, size_t start) {
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


std::string ExpressionEvaluator::preprocessExpression(const std::string& expression) {

    std::string cleanedExpression = ExpressionEvaluator::addParentheses(expression);

    // 检查合法性
    if (!hasInvalidCharacters(cleanedExpression)) {
        throw std::invalid_argument("表达式包含非法字符");
    }
    if (!areParenthesesBalanced(cleanedExpression)) {
        throw std::invalid_argument("表达式中的括号不平衡");
    }
    if (hasExtraDecimalPoint(cleanedExpression)) {
        throw std::invalid_argument("表达式包含多余的小数点");
    }
    if (hasInvalidOperatorSequence(cleanedExpression)) {
        throw std::invalid_argument("表达式包含无效的运算符序列");
    }

    std::string result_1;
    int signCount = 0;
    bool inConsecutiveSigns = false;

    for (size_t i = 0; i < cleanedExpression.size(); ++i) {
        char c = cleanedExpression[i];

        if (c == '+' || c == '-') {
            if (!inConsecutiveSigns) {
                inConsecutiveSigns = true;
                signCount = 0;
            }
            signCount += (c == '-') ? 1 : 0;
        } else {
            if (inConsecutiveSigns) {
                result_1 += (signCount % 2 == 0) ? '+' : '-';
                inConsecutiveSigns = false;
                signCount = 0;
            }
            result_1 += c;
        }
    }

    // 遇到结尾的连续符号
    if (inConsecutiveSigns) {
        result_1 += (signCount % 2 == 0) ? '+' : '-';
    }

    std::string result_2 = result_1;
    bool modified;

    do {
        modified = false;
        std::string temp_result;

        for (size_t i = 0; i < result_2.size(); ++i) {
            char c = result_2[i];

            // 检查符号后接的特殊情况
            if ((c == '+' || c == '-' || c == '*' || c == '/' || c == '(')) {
                char nextChar = result_2[i + 1];

                // 处理符号后接 'e' 的情况
                if (nextChar == 'e') {
                    temp_result += c;
                    temp_result += "1e";
                    ++i;  // 跳过下一个字符 'e'
                    modified = true;
                }
                // 处理符号后接 '.' 的情况
                else if (nextChar == '.') {
                    temp_result += c;
                    temp_result += "0.";
                    ++i;  // 跳过下一个字符 '.'
                    modified = true;
                }
                // 处理 '*+' 和 '/+' 的情况
                else if ((c == '*' || c == '/') && nextChar == '+') {
                    temp_result += c;
                    ++i;  // 跳过下一个字符 '+'
                    modified = true;
                }
                // 处理 '(+' 和 '(-' 的情况
                else if (c == '(' && (nextChar == '+' || nextChar == '-')) {
                    temp_result += "(0";
                    temp_result += nextChar;
                    ++i;  // 跳过下一个字符 '+' 或 '-'
                    modified = true;
                } else {
                    temp_result += c;
                }
            }
            // 处理 'e.' 的情况
            else if (c == 'e' && result_2[i + 1] == '.') {
                temp_result += "e0.";
                ++i;  // 跳过下一个字符 '.'
                modified = true;
            } else {
                temp_result += c;
            }
        }

        // 更新 result_2 为 temp_result
        result_2 = temp_result;

    } while (modified);  // 当字符串在一次扫描中没有任何变化时，停止循环

    std::string previousResult;
    std::string result_3 = result_2;

    do {
        previousResult = result_3;  // 保存当前结果以便检查是否有变更
        std::string tempResult;
        size_t i = 0;

        while (i < result_3.size()) {
            // 检查 "*-", "/-" 模式并开始处理带括号的负号
            if ((result_3[i] == '*' || result_3[i] == '/') && result_3[i + 1] == '-') {
                tempResult += result_3[i];  // 添加 "*" 或 "/"
                tempResult += "(0-";        // 添加括号和负号
                i += 2;                     // 跳过 "*-"、"/-"

                if (result_3[i] == '(') {
                    // 处理负号后是括号的情况，找到对应的闭括号位置
                    int rightOperandEnd = findRightOperandEnd(result_3, i - 1);
                    tempResult += result_3.substr(i, rightOperandEnd - i);
                    tempResult += ")";
                    i = rightOperandEnd;
                } else {
                    // 处理负号后的数字或小数部分
                    while (i < result_3.size() && (std::isdigit(result_3[i]) || result_3[i] == '.')) {
                        tempResult += result_3[i];
                        ++i;
                    }

                    // 检查下一个运算符的优先级
                    if (i < result_3.size()) {
                        if (result_3[i] == ')' || result_3[i] == '+' || result_3[i] == '-') {
                            tempResult += ")";
                        } else if (result_3[i] == '*' || result_3[i] == '/' || result_3[i] == 'e') {
                            int another_rightOperandEnd = findRightOperandEnd(result_3, i);
                            tempResult += result_3.substr(i, another_rightOperandEnd - i);
                            tempResult += ")";
                            i = another_rightOperandEnd;
                        }
                    }
                }
            } else if (result_3[i] == 'e' && result_3[i + 1] == '-') {
                tempResult += result_3[i];
                tempResult += "(0-";
                i += 2; 

                if (result_3[i] == '(') {
                    // 处理负号后是括号的情况，找到对应的闭括号位置
                    int rightOperandEnd = findRightOperandEnd(result_3, i - 1);
                    tempResult += result_3.substr(i, rightOperandEnd - i);
                    tempResult += ")";
                    i = rightOperandEnd;
                } else {
                    while (i < result_3.size() && (std::isdigit(result_3[i]) || result_3[i] == '.')) {
                        tempResult += result_3[i];
                        ++i;
                    }
                    tempResult += ")";
                }
            } else {
                tempResult += result_3[i];
                ++i;
            }
        }
        result_3 = tempResult;  // 更新 result_3 为当前扫描的结果

    } while (result_3 != previousResult);  // 如果没有新的变更则结束循环

    return result_3;

}

std::vector<std::string> ExpressionEvaluator::tokenizeExpression(const std::string& expression) {
    std::vector<std::string> tokens;
    std::string number;

    for (size_t i = 0; i < expression.size(); ++i) {
        char c = expression[i];

        if (std::isdigit(c) || c == '.') {
            // 构建数值（double）
            number += c;
        } else {
            if (!number.empty()) {
                tokens.push_back(number);  // 将完成的数值加入 tokens
                number.clear();
            }

            if (c == '+' || c == '-' || c == '*' || c == '/' || c == 'e' || c == '(' || c == ')') {
                tokens.push_back(std::string(1, c));  // 添加单个运算符或括号
            }
        }
    }

    // 如果表达式以数值结尾，将最后一个数值添加到 tokens
    if (!number.empty()) {
        tokens.push_back(number);
    }

    return tokens;
}

std::string ExpressionEvaluator::infixToPostfix(const std::string& expression) {
    std::vector<std::string> tokens = tokenizeExpression(expression);
    std::stack<std::string> stack;
    std::string postfix;

    for (const std::string& token : tokens) {
        // 数值直接输出到后缀表达式
        if (std::isdigit(token[0]) || (token.size() > 1 && (std::isdigit(token[1]) || token[0] == '.'))) {
            postfix += token + " ";
        }
        // 左括号直接入栈
        else if (token == "(") {
            stack.push(token);
        }
        // 遇到右括号，弹出直到左括号
        else if (token == ")") {
            while (!stack.empty() && stack.top() != "(") {
                postfix += stack.top() + " ";
                stack.pop();
            }
            if (!stack.empty()) stack.pop(); // 弹出左括号
        }
        // 遇到运算符
        else if (isOperator(token[0])) {
            while (!stack.empty() && getPrecedence(stack.top()[0]) >= getPrecedence(token[0])) {
                postfix += stack.top() + " ";
                stack.pop();
            }
            stack.push(token);
        }
    }

    // 将栈中剩余的所有运算符弹出到后缀表达式
    while (!stack.empty()) {
        postfix += stack.top() + " ";
        stack.pop();
    }

    return postfix;
}

double ExpressionEvaluator::evaluatePostfix(const std::string& postfixExpression) {
    std::istringstream tokens(postfixExpression);
    std::stack<double> stack;
    std::string token;

    while (tokens >> token) {
        // 判断是否为数字
        if (std::isdigit(token[0]) || (token.size() > 1 && token[0] == '-')) {
            stack.push(std::stod(token));
        } 
        // 判断是否为运算符
        else if (isOperator(token[0])) {
            if (stack.size() < 2) {
                throw std::invalid_argument("Invalid postfix expression");
            }
            double right = stack.top(); stack.pop();
            double left = stack.top(); stack.pop();

            // 使用 applyOperation 执行对应操作
            double result = applyOperation(left, right, token[0]);
            stack.push(result);
        } else {
            throw std::invalid_argument("Unknown token in postfix expression: " + token);
        }
    }

    if (stack.size() != 1) {
        throw std::invalid_argument("Invalid postfix expression");
    }

    return stack.top();
}

