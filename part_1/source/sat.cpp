#include "sat.h"
#include <iostream>

std::vector<alphabet> parse(std::string exp) {
    std::vector<alphabet> expression;
    for(char& c : exp) {
        switch(c) {
        case 'w':
            expression.push_back(var_w);
            break;
        case 'x':
            expression.push_back(var_x);
            break;
        case 'y':
            expression.push_back(var_y);
            break;
        case 'z':
            expression.push_back(var_z);
            break;
        case '!':
            expression.push_back(neg);
            break;
        case '(':
            expression.push_back(open_par);
            break;
        case ')':
            expression.push_back(close_par);
            break;
        case ',':
            expression.push_back(comma);
            break;
        default:
            expression.push_back(invalid);
            break;
        }
    }

    return expression;
}
