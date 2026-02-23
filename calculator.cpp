#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include "calculator.h"

bool RunCalculatorCycle() {
    
    std::string str_input;
    std::vector<Number> results;
    Number number_1 = 0;
    Number number_2 = 0;
    Number memory_cell = 0;
    bool is_memory_cell_empty = true;
    std::string operation = "";
    int j = 0;
    
    if (!ReadNumber(number_1)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }
    j++;
    while (true) {

        if (j % 2 == 0) {
            if (!ReadNumber(number_2)) {
                std::cerr << "Error: Numeric operand expected" << std::endl;
                return false;
            }
            j++;
            number_1 = Action(number_1, number_2, operation);
        }
        else {
            try {
                str_input = ReadOperator();
            }
            catch (std::exception&) {
                return false;
            }
            if (str_input == "q") {
                break;
            }else if (str_input == "=") {
                results.push_back(number_1);
            }
            else if (str_input == "l") {
                if (is_memory_cell_empty) {
                    Print(results);
                    std::cerr << "Error: Memory is empty" << std::endl;
                    return false;
                }
                number_1 = memory_cell;
            } 
            else if (str_input == "s") {
                memory_cell = results.at(results.size() - 1);
                is_memory_cell_empty = false;
            }
            else if (str_input == "c") {
                number_1 = 0;
            }
            else {
                operation = str_input;
                j++;
            }
        }
    }
    Print(results);
    return true;
}


bool ReadNumber(Number& result) {
    std::string str_input;
    std::cin >> str_input;
    try {
        result = std::stod(str_input);
        return true;
    }
    catch (const std::invalid_argument&) {
    }
    return false;
}

std::string ReadOperator() {
    std::string str_input;
    std::cin >> str_input;

    if (str_input == "=" || str_input == "s" || str_input == "l" || str_input == "q" || str_input == "c" ||
        str_input == "+" || str_input == "-" || str_input == "*" || str_input == "/" || str_input == "**" ||
        str_input == ":") {
        return str_input;
    }
    else {
        std::cerr << "Error: Unknown token " << str_input << std::endl;
        throw std::exception();
    }
}

double Action(double number_1, double number_2, std::string operation) {
    if (operation == "+") {
        number_1 += number_2;
    }
    else if (operation == "-") {
        number_1 -= number_2;
    }
    else if (operation == "*") {
        number_1 *= number_2;
    }
    else if (operation == "/") {
        number_1 /= number_2;
    }
    else if (operation == "**") {
        number_1 = std::pow(number_1, number_2);
    }
    else if (operation == ":") {
        number_1 = number_2;
    }
    return Round(number_1);
}

double Round(double number) {
    int n = (int)number;
    double d = (number - n) * 10;
    if (d < 0) {
        d *= -1;
        if (d - (int)d > 0.5) {
            d = std::round(d) / 10;
        }
        else {
            d /= 10;
        }
        d *= -1;
    }
    else {
        if (d - (int)d > 0.5) {
            d = std::round(d) / 10;
        }
        else {
            d /= 10;
        }
    }
    return (double)n + d;
}

void Print(const std::vector<double>& results) {
    for (double d : results) {
        std::cout << d << std::endl;
    }
}