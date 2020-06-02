#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include "formula.h" 
#include "dpll.h"

int main(const int argc, const char* argv[]) {
    std::cout << "Hello, World!" << std::endl;
    std::cout << "Enter expression" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::cout << "RECIVED INPUT: " << input << std::endl;

    expression_t exp = parse(input); 

    /**/ std::cout << "Checking if input is alphabetically correct" << std::endl;
    if ( std::find(exp.begin(), exp.end(), invalid) != exp.end())  {
        std::cout << "Error: invalid input" << std::endl; 
        return 1;
    }

    /**/ std::cout << "Checking if syntax is valid" << std::endl;
    formula_t formula = make_formula(exp);

    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            if ( formula[i][j] == inv ) {
                std::cout << "Error: invalid syntax" << std::endl; 
                return 1;
            }
        }
    }

    /**/ std::cout << "Printing formula" << std::endl;
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            show_literal(formula[i][j]);
        }
        std::cout << std::endl;
    }

    /**/ std::cout << "Running algorithm" << std::endl;
    if ( DPLL(formula) )    { std::cout << "SAT" << std::endl; }
    else                    { std::cout << "UNSAT" << std::endl; } 


    return 0;
}
