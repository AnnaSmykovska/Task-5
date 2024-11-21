#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <stdexcept>
#include <stack>

const int STACK_SIZE = 100;

class Stack {
private:
    std::array<int, STACK_SIZE> data;
    int top;

public:
    Stack() : top(-1) {}

    void push(int value) {
        if (top == STACK_SIZE - 1) {
            throw std::overflow_error("Stack overflow");
        }
        data[++top] = value;
    }
    int pop() {
        if (top == -1) {
            throw std::underflow_error("Stack underflow");
        }
        return data[top--];
    }
    bool isEmpty() const {
        return top == -1;
    }
};

std::string convertTo(const std::string& expression) {
    std::stack<std::string> infixStack;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (infixStack.size() < 2) throw std::invalid_argument("Invalid postfix expression");
            std::string b = infixStack.top(); infixStack.pop();
            std::string a = infixStack.top(); infixStack.pop();
            std::string result = "(" + a + " " + token + " " + b + ")";
            infixStack.push(result);
        }
        else {
            infixStack.push(token);
        }
    }
    if (infixStack.size() != 1) throw std::invalid_argument("Invalid postfix expression");
    return infixStack.top();
}

int evaluatePostfix(const std::string& expression) {
    Stack stack;
    std::stringstream ss(expression);
    std::string token;

    while (ss >> token) {
        if (token == "+" || token == "-" || token == "*" || token == "/") {
            if (stack.isEmpty()) throw std::invalid_argument("Invalid expression");
            int b = stack.pop();
            if (stack.isEmpty()) throw std::invalid_argument("Invalid expression");
            int a = stack.pop();
            int result;
            if (token == "+") result = a + b;
            else if (token == "-") result = a - b;
            else if (token == "*") result = a * b;
            else if (token == "/") {
                if (b == 0) throw std::runtime_error("Division by zero");
                result = a / b;
            }
            stack.push(result);
        }
        else {
            stack.push(std::stoi(token));
        }
    }
    if (stack.isEmpty()) throw std::invalid_argument("Invalid expression");
    int result = stack.pop();
    if (!stack.isEmpty()) throw std::invalid_argument("Invalid expression");
    return result;
}

int main() {
    std::string expression;
    std::cout << "Enter a postfix expression: ";
    std::getline(std::cin, expression);

    try {
        std::string convertExpression = convertTo(expression);
        std::cout << "Equivalent to: " << convertExpression << std::endl;
        int result = evaluatePostfix(expression);
        std::cout << "The result of the expression is: " << result << std::endl;
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }
    return 0;
}