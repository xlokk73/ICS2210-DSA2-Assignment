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

void show(formula_t formula) {
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            show_literal(formula[i][j]);
        }
        std::cout << std::endl;
    }
}

bool DPLL(formula_t formula) {
    std::cout << "Starting DPLL" << std::endl;
    show(formula);

    if ( contains_trivially_unsat(formula) )        { return false; }

    if ( formula.size() == 0 )                      { return true; }

    if ( contains_empty_clause(formula) )           { return false; } 

    loop:
    for(int i = 0; i < formula.size(); ++i) {
        if ( formula[i].size() == 1) {
            formula = apply_1_lit_rule(formula[i][0], formula);
            goto loop;
        }
    }

    formula = apply_pure_lit_rule(formula);


    // DPLL
    literal_t l = choose_literal(formula);
    literal_t nl;
    nl.var = l.var;
    nl.is_neg = !l.is_neg;

    formula_t formula1 = formula;
    formula_t formula2 = formula;

    formula1.push_back({l});
    formula2.push_back({nl});

    return DPLL(formula1) || DPLL(formula2);
}

literal_t choose_literal(formula_t formula) {
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            return formula[i][j];
        }
    }

    return {};
}

bool contains(literal_t literal, clause_t clause) {

    for(int i = 0; i < clause.size(); ++i) {
        if(literal.var == clause[i].var && literal.is_neg == clause[i].is_neg) { return true; }
    }

    return false;

}

bool is_pure(variable v, bool nval, formula_t formula) {
    bool exists = false;
    std::cout << "HERE 4" << std::endl;
    std::cout << "FORMULA SIZE: " << formula.size() << std::endl;
    
    for(int i = 0; i < formula.size(); ++i) {
        std::cout << "HERE 5" << std::endl;
        for(int j = 0; j < formula[i].size(); ++j) {
            std::cout << "HERE 3" << std::endl;
            if ( formula[i][j].var == v && formula[i][j].is_neg == nval ) { exists = true; }
            else if ( formula[i][j].var == v && formula[i][j].is_neg != nval ) { return false; }
        }
    }

    return exists;
}

formula_t apply_pure_lit_rule(formula_t formula) {
    formula_t new_formula;

    // Find pure literals
    std::vector<literal_t> pure_literals;
    literal_t literal;
    
    std::vector<variable> var_list = { w, x, y, z };

    for(int i = 0; i < var_list.size(); ++i) {
        std::cout << "VARIABLE: " << var_list[i] << " ";
        
        if ( is_pure(var_list[i], false, formula) ) { 
            std::cout << "HERE 1" << std::endl;
            literal.var = var_list[i];
            literal.is_neg = false;
            pure_literals.push_back(literal);
        }
        else if ( is_pure(var_list[i], true, formula) ) {
            std::cout << "HERE 2" << std::endl;
            literal.var = var_list[i];
            literal.is_neg = true;
            pure_literals.push_back(literal);
        }
    }
          
    std::cout << "\nPRINTING PURE LITERALS" << std::endl;
    for(int i = 0; i < pure_literals.size(); ++i) {
        show_literal(pure_literals[i]);
    }
    std::cout << std::endl;

    // Remove any clause with pure literals

    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < pure_literals.size(); ++j) {
            if ( contains(pure_literals[j], formula[i]) ) {}
            else { new_formula.push_back(formula[i]); }
        }
    }

    return new_formula;
}




std::vector<clause_t> apply_1_lit_rule(literal_t u, std::vector<clause_t> formula) {
    variable v = u.var;
    bool has_u = false;
    bool is_nv = u.is_neg;

    std::vector<clause_t> new_formula; 
    std::vector<literal_t> new_clause;


    // For each clause
    for(int i = 0; i < formula.size(); ++i) {
        new_clause = {};

        // Create a new formula without v clauses and without !v in any clause
        for(int j = 0; j < formula[i].size(); ++j) {
            if (formula[i][j].var == v && is_nv != formula[i][j].is_neg ) {}
            else if (formula[i].size()==1 && formula[i][0].var == v && is_nv == formula[i][0].is_neg) { has_u = true; } 
            else { new_clause.push_back(formula[i][j]); }
        }

        if ( !has_u ) {
            new_formula.push_back(new_clause);
        }

        has_u = false;
    }

    return new_formula;
}

bool contains_contradiction(formula_t formula, variable v) {

    int formula_length = formula.size();

    // Check for {v}
    for(int i = 0; i < formula_length; ++i) {
        if ( formula[i].size() != 1 ) {}
        else if ( formula[i][0].var == v && !formula[i][0].is_neg ) {
            // Check for {!v}
            for(int j = 0; j < formula_length; ++j) {
                if ( formula[j].size() != 1 ) {}
                else if ( formula[j][0].var == v && formula[j][0].is_neg ) {
                    return true;
                }
            }
        }
    }
    
    return false;
}
    
bool contains_trivially_unsat(formula_t formula) {
    if ( contains_contradiction(formula, w)
        || contains_contradiction(formula, x)
        || contains_contradiction(formula, y)
        || contains_contradiction(formula, z) ) {
            return true;
    }

    return false;
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
