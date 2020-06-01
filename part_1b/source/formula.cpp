#include "formula.h"
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

void show_literal(literal_e literal) { 

    switch(literal) {
    case w:
        std::cout << "w ";
        break;
    case nw:
        std::cout << "!w ";
        break;
    case x:
        std::cout << "x ";
        break;
    case nx:
        std::cout << "!x ";
        break;
    case y:
        std::cout << "y ";
        break;
    case ny:
        std::cout << "ny ";
        break;
    case z:
        std::cout << "z ";
        break;
    case nz:
        std::cout << "!z ";
        break;
    default:
        std::cout << "Invalid";
        break;
    }
}    


formula_t make_formula(expression_t exp) {
    literal_e current_literal;
    clause_t current_clause = {};
    formula_t formula = {};
    bool in_par = false;
    bool in_neg = false;
    bool in_comma = false;

    for ( std::size_t i = 0; i < exp.size(); ++i ) {
        switch(exp[i]) {

        case open_par:
            if (in_par)                             { return {{inv}}; }
            if (in_neg)                             { return {{inv}}; }

            in_par = true;
            in_neg = false;
            in_comma = false;

            break;

        case close_par:
            if (!in_par)    { return {{inv}}; }
            if (in_neg)     { return {{inv}}; }
            if (in_comma)   { return {{inv}}; }

            in_par = false;
            in_neg = false;
            in_comma = false;

            formula.push_back(current_clause);

            break;

        case neg:
            if (in_neg)                             { return {{inv}}; }

            in_neg = true;

            break; 

        case comma:
            if (in_comma)                               { return {{inv}}; } 
            if (in_neg)                                 { return {{inv}}; }

            in_neg = false;
            in_comma = false;
            
            break; 

        case var_w:
            if (in_par) {
                if (in_neg) { current_clause.push_back(nw); }
                else        { current_clause.push_back(w); }
            }

            else {
                if (in_neg) { formula.push_back({nw}); }
                else        { formula.push_back({w}); }
            }

            in_neg = false;
            in_comma = false;

            break;

        case var_x:
            if (in_par) {
                if (in_neg) { current_clause.push_back(nx); }
                else        { current_clause.push_back(x); }
            }

            else {
                if (in_neg) { formula.push_back({nx}); }
                else        { formula.push_back({x}); }
            }

            in_neg = false;
            in_comma = false;


            break;

        case var_y:
            if (in_par) {
                if (in_neg) { current_clause.push_back(ny); }
                else        { current_clause.push_back(y); }
            }

            else {
                if (in_neg) { formula.push_back({ny}); }
                else        { formula.push_back({y}); }
            }

            in_neg = false;
            in_comma = false;


            break;

        case var_z:
            if (in_par) {
                if (in_neg) { current_clause.push_back(nz); }
                else        { current_clause.push_back(z); }
            }

            else {
                if (in_neg) { formula.push_back({nz}); }
                else        { formula.push_back({z}); }
            }

            in_neg = false;
            in_comma = false;


            break;

        default:
            current_literal = inv;
            current_clause = {current_literal};
            formula = {current_clause};
            return formula; 
        }
    }
    return formula;
}

void show_formula(formula_t formula) {
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            show_literal(formula[i][j]);
        }
        std::cout << std::endl;
    }
}


