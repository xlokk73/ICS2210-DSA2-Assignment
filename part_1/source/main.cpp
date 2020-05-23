#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
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
    if (formula[0][0].var == inv) { 
        std::cout << "Error: invalid formula" << std::endl;
        return 1;
    }

    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            show_literal(formula[i][j]);
        }
        std::cout << std::endl;
    }

    return 0;
}
