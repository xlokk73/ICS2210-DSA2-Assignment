#include <iostream>
#include <string>
#include <vector>
#include "sat.h" 

int main(const int argc, const char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Enter expression" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::cout << "RECIVED INPUT: " << input << std::endl;

    expression_t exp = parse(input); 

    if ( std::find(exp.begin(), exp.end(), invalid) != exp.end())  {
        std::cout << "Error: invalid input" << std::endl; 
        return 1;
    }

    formula_t formula = make_formula(exp);

    for(std::size_t i = 0; i < formula.size(); ++i) {
        for(std::size_t j = 0; j < formula[i].size(); ++j) {
            std::cout << "hello ";
        }
        std::cout << std::endl;
    }

    return 0;
}
