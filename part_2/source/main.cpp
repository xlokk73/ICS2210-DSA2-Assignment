#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "huffman.h"

int main(const int argc, const char* argv[]) {
    std::cout << "Hello, World!" << std::endl;

    if ( argc != 2 ) { 
        std::cout << "Error: invalid argument count" << std::endl;
        return 1;
    }

    std::string filename(argv[1]);

    std::ifstream stream(filename);
    std::string content ( (std::istreambuf_iterator<char>(stream) ),
                          (std::istreambuf_iterator<char>()       ) );
    content.pop_back();
    
    for (char const &c: content) {
		if ( (c>47 && c<58) || (c>64 && c<91) || (c>96 && c<123) ) {}

        else { std::cout << "Error: invalid characters in file" << std::endl; return 1; }
	}

    stream.close();

    std::cout << "Building tree: " << std::endl;
    huffman(content);

    std::cout << "Printing tree: " << std::endl;
    show_table(trees[0], "");

    destroy(trees[0]);
    return 0;
}
