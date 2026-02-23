#pragma once

#include <string>
#include <vector>

using Number = double;

double Action(double number_1, double number_2, std::string operation);

double Round(double number);

bool ReadNumber(Number& result);

std::string ReadOperator();

bool RunCalculatorCycle();

void Print(const std::vector<double>& results);