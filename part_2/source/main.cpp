#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main(const int argc, const char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    if ( argc != 2 ) { 
        std::cout << "Error: invalid argument count" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);

    std::ifstream stream(filename);

    char c;
    while(stream.get(c)) {
        std::cout << "char: " << c << std::endl;
    }

    stream.close();

    return 0;
}
