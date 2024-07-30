#pragma once
#include <exception>
using namespace std;

class graphException : public exception {
public:
    const char* what() const noexcept override {
        return "Graph exception";
    }
};

class invalidInputException : public graphException {
public:
    const char* what() const noexcept override {
        return "Invalid input exception";
    }
};

