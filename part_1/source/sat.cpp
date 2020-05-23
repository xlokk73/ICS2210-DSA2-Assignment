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
        case ' ':
            break;
        case '\n':
            break;
        default:
            exp.push_back(invalid);
            break;
        }
    }

    return exp;
}

void show_literal(literal_t literal) { 
    if ( literal.is_neg ) { std::cout << "!"; }

    switch(literal.var) {
    case w:
        std::cout << "w ";
        break;
    case x:
        std::cout << "x ";
        break;
    case y:
        std::cout << "y ";
        break;
    case z:
        std::cout << "z ";
        break;
    default:
        std::cout << "Invalid";
        break;
    }
}    

formula_t make_formula(expression_t exp) {
    literal_t current_literal;
    clause_t current_clause = {};
    formula_t formula = {};
    bool in_par = false;
    bool in_neg = false;
    bool in_comma = false;

    for ( std::size_t i = 0; i < exp.size(); ++i ) {
        switch(exp[i]) {

        case open_par:
            in_comma = false;
            in_par = true;
            break;

        case close_par:
            if(in_comma || in_neg) { 
                current_literal.var = inv;
                current_clause = {current_literal};
                formula = {current_clause};
                return formula; 
            }
            in_par = false;
            formula.push_back(current_clause);
            current_clause = {};
            break;

        case neg:
            in_comma = false;
            in_neg = true; 
            break; 

        case comma:
            if(in_comma || in_neg) { 
                current_literal.var = inv;
                current_clause = {current_literal};
                formula = {current_clause};
                return formula; 
            }

            else { 
                in_comma = true; 
                break; 
            }

        case var_w:
            in_comma = false;
            current_literal.var = w;

            if(in_neg)  { current_literal.is_neg = true; }
            else        { current_literal.is_neg = false; }

            in_neg = false;

            if(in_par) { 
                current_clause.push_back(current_literal); 
            } 

            else { 
                current_clause = { current_literal };
                formula.push_back(current_clause);
                current_clause = {};
            }
            break;

        case var_x:
            in_comma = false;
            current_literal.var = x;

            if(in_neg)  { current_literal.is_neg = true; }
            else        { current_literal.is_neg = false; }

            in_neg = false;

            if(in_par) { 
                current_clause.push_back(current_literal); 
            } 

            else { 
                current_clause = { current_literal };
                formula.push_back(current_clause);
                current_clause = {};
            }
            break;

        case var_y:
            in_comma = false;
            current_literal.var = y;

            if(in_neg)  { current_literal.is_neg = true; }
            else        { current_literal.is_neg = false; }

            in_neg = false;

            if(in_par) { 
                current_clause.push_back(current_literal); 
            } 

            else { 
                current_clause = { current_literal };
                formula.push_back(current_clause);
                current_clause = {};
            }
            break;

        case var_z:
            in_comma = false;
            current_literal.var = z;

            if(in_neg)  { current_literal.is_neg = true; }
            else        { current_literal.is_neg = false; }

            in_neg = false;

            if(in_par) { 
                current_clause.push_back(current_literal); 
            } 

            else { 
                current_clause = { current_literal };
                formula.push_back(current_clause);
                current_clause = {};
            }
            break;

        default:
            current_literal.var = inv;
            current_clause = {current_literal};
            formula = {current_clause};
            return formula; 
        }
    }
    return formula;
}

bool DPLL(formula_t formula) {
    std::cout << "Starting DPLL" << std::endl;
    
    // if ( is_consistent_set_of_literals(formula) )   { return true; }

    if ( contains_empty_clause(formula) )           { return false; } 

    return true;
}

bool is_consistent_set_of_literals(formula_t form) {
    return true;
}

bool contains_empty_clause(formula_t formula) {
    for(int i = 0; i < formula.size(); ++i) {
        if ( formula[i].size() == 0 ) {
            return true;
        }
    }
    
    return false;
}
