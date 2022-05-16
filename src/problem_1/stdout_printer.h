#include "printer.h"
#include <iostream>

class StdoutPrinter : public Printer {
public:
    void print(std::string val) override {

        std::cout << val << std::endl;
    }
};