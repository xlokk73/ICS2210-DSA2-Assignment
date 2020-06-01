#include "formula.h"
#include "dpll.h"
#include <iostream>

bool DPLL(formula_t formula) {
    std::cout << "Starting DPLL" << std::endl;
    show_formula(formula);

    formula = remove_trivially_sat(formula);
    std::cout << "CURRENT FORMULA:\n";
    show_formula(formula);

    if ( formula.size() == 0 )                      { return true; }

    /*
    if ( contains_trivially_unsat(formula) )        { return false; }


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
    */
    std::cout << "HERE\n";
    return false;
}

formula_t remove_trivially_sat(formula_t formula) {
    // index_var[] = { index of w, index of x, ..., index of z }
    // index_nvar[] = { index of !w, index of !x, ..., index of !z }
    int index_var[4]  = {-1, -1, -1, -1};
    int index_nvar[4] = {-1, -1, -1, -1};

    // Find clauses with single variables
    for(int i = 0; i < formula.size(); ++i) {
        if (formula[i].size() == 1) {
            switch(formula[i][0]) {
            case w:
                index_var[0] = i;
                break;
            case x:
                index_var[1] = i;
                break;
            case y:
                index_var[2] = i;
                break;
            case z:
                index_var[3] = i;
                break;
            case nw:
                index_nvar[0] = i;
                break;
            case nx:
                index_nvar[1] = i;
                break;
            case ny:
                index_nvar[2] = i;
                break;
            case nz:
                index_nvar[3] = i;
                break;
            default:
                return formula;
            }
        }
    }

    for(int i = 0; i < 4; ++i) {
        if (index_var[i] != -1 && index_nvar[i] != -1) {
            formula.erase(formula.begin() + index_var[i]); 
            
            if (index_var[i] > index_nvar[i]) {
                formula.erase(formula.begin() + index_nvar[i]);
            }
            else {
                formula.erase(formula.begin() + index_nvar[i] - 1);
            }
        }
    }

    return formula;
}

/* 
literal_t choose_literal(formula_t formula) {
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            return formula[i][j];
        }
    }

    return {};
}

bool contains(literal_e literal, clause_t clause) {

    for(int i = 0; i < clause.size(); ++i) {
        if(literal.var == clause[i].var && literal.is_neg == clause[i].is_neg) { return true; }
    }

    return false;

}

bool is_pure(variable v, bool nval, formula_t formula) {
    bool exists = false;
    
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
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
            literal.var = var_list[i];
            literal.is_neg = false;
            pure_literals.push_back(literal);
        }
        else if ( is_pure(var_list[i], true, formula) ) {
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
*/
