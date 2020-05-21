#include "sat.h"
#include <iostream>

expression_t parse(std::string str_exp) {
    expression_t exp;
    for(char& c : str_exp) {
        switch(c) {
        case 'w':
            exp.push_back(var_w);
            break;
        case 'x':
            exp.push_back(var_x);
            break;
        case 'y':
            exp.push_back(var_y);
            break;
        case 'z':
            exp.push_back(var_z);
            break;
        case '!':
            exp.push_back(neg);
            break;
        case '(':
            exp.push_back(open_par);
            break;
        case ')':
            exp.push_back(close_par);
            break;
        case ',':
            exp.push_back(comma);
            break;
        default:
            exp.push_back(invalid);
            break;
        }
    }

    return exp;
}

formula_t make_formula(expression_t exp) {
    clause_t clause_ = {};

    return {};
}

bool DPLL(formula_t form) {
    std::cout << "Starting DPLL" << std::endl;
    
    if ( is_consistent_set_of_literals(form) )   { return true; }

    if ( contains_empty_clause(form) )           { return false; } 

    return true;
}

bool is_consistent_set_of_literals(formula_t form) {
    return true;
}

bool contains_empty_clause(formula_t form) {
    return true;
}
