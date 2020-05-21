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

    std::vector<alphabet> expression = parse(all_args[1]); 

    for(std::size_t i=0; i<expression.size(); ++i)
        std::cout << expression[i] << '\n';
    
    return 0;
}
