#include <iostream>
#include <string>
#include <vector>
#include "sat.h" 

int main(const int argc, const char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    if ( argc != 2 ) {
        std::cout << "Error: invalid number of parameters" << std::endl;
        return 0;
    }

    std::vector<std::string> all_args(argv, argv + argc);

    expression_t exp = parse(all_args[1]); 

    if ( std::find(exp.begin(), exp.end(), invalid) != exp.end())  {
        std::cout << "Error: invalid input" << std::endl; 
        return 1;
    }

    formula_t form = make_formula(exp);

    return 0;
}
