#include "formula.h"
#include "dpll.h"
#include <iostream>

bool DPLL(formula_t formula) {
    std::cout << "Starting DPLL" << std::endl;
    show_formula(formula);

    std::cout << "Removing trivially sat" << std::endl;
    formula = remove_trivially_sat(formula);
    show_formula(formula);

    if ( formula.size() == 0 )                      { return true; }

    if ( contains_trivially_unsat(formula) )        { return false; }

    if ( contains_empty_clause(formula) )           { return false; } 


    std::cout << "Applying one lit rule\n";
    exhaust:
    for(int i = 0; i < formula.size(); ++i) {
        if (formula[i].size() == 1) {
            formula = apply_1_lit_rule(formula[i][0], formula);
            goto exhaust;
        }
    }
    show_formula(formula);
    

    std::cout << "Applying pure lit rule\n";
    formula = apply_pure_lit_rule(formula);
    show_formula(formula);


    // DPLL
    literal_e l = choose_literal(formula);
    literal_e nl = negate(l);

    formula_t formula1 = formula;
    formula_t formula2 = formula;

    formula1.push_back({l});
    formula2.push_back({nl});

    return DPLL(formula1) || DPLL(formula2);
}

literal_e choose_literal(formula_t formula) {
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            return formula[i][j];
        }
    }

    return {};
}

literal_e negate(literal_e literal) {
    switch(literal) {
    case w:
        return nw;
    case x:
        return nx;
    case y:
        return ny;
    case z:
        return nz;
    case nw:
        return w;
    case nx:
        return x;
    case ny:
        return y;
    case nz:
        return z;
    case inv:
        return inv;
    }
}

bool greater_than (int i,int j) { return (i>j); }

formula_t remove_trivially_sat(formula_t formula) {
    // index_var[] = { index of w, index of x, ..., index of z }
    // index_nvar[] = { index of !w, index of !x, ..., index of !z }
    int index_var[8]  = {-1, -1, -1, -1, -1, -1, -1, -1};

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
                index_var[4] = i;
                break;
            case nx:
                index_var[5] = i;
                break;
            case ny:
                index_var[6] = i;
                break;
            case nz:
                index_var[7] = i;
                break;
            default:
                return formula;
            }
        }
    }

    std::vector<int> to_remove;
    for(int i = 0; i < 4; ++i) {
        if(index_var[i] != -1 && index_var[i + 4] != -1) {
            to_remove.push_back(index_var[i]);
        }
    }

    std::sort (to_remove.begin(), to_remove.end(), greater_than); 
    for(int i = 0; i < to_remove.size(); ++i) {
        formula.erase(formula.begin() + to_remove[i]);
    }

    return formula;
}

bool contains_in_same_clause(formula_t formula, literal_e v, literal_e nv) {

    bool contains_v = false;
    bool contains_nv = false;

    for(int i = 0 ; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            if (formula[i][j] == v)     { contains_v = true; }
            if (formula[i][j] == nv)    { contains_nv = true; }
        }

        if (contains_v && contains_nv) { return true; }
        else { 
            contains_v = false;
            contains_nv = false;
        }
    }
    
    return false;
}
    
bool contains_trivially_unsat(formula_t formula) {
    if ( contains_in_same_clause(formula, w, nw)
        || contains_in_same_clause(formula, x, nx)
        || contains_in_same_clause(formula, y, ny)
        || contains_in_same_clause(formula, z, nz) ) {
            return true;
    }

    return false;
}

formula_t apply_1_lit_rule(literal_e u, formula_t formula) {
    literal_e nu;
    switch(u) {
    case w:
        nu = nw;
        break;
    case x:
        nu = nx;
        break;
    case y:
        nu = ny;
        break;
    case z:
        nu = nz;
        break;
    case nw:
        nu = w;
        break;
    case nx:
        nu = x;
        break;
    case ny:
        nu = y;
        break;
    case nz:
        nu = z;
        break;
    default:
        nu = inv;
        break;
    }

    formula_t new_formula = {};
    clause_t current_clause = {};
    
    for(int i = 0; i < formula.size(); ++i) {
        if (formula[i].size() == 1 && formula[i][0] == u) {}
        else {
            for(int j = 0; j < formula[i].size(); ++j) {
                if (formula[i][j] == nu) {}
                else { current_clause.push_back(formula[i][j]); }
            }

            new_formula.push_back(current_clause);
            current_clause = {};
        }
    }

    return new_formula;
}

bool contains_empty_clause(formula_t formula) {
    for(int i = 0; i < formula.size(); ++i) {
        if (formula[i].size() == 0) { return true; }
    }
    
    return false;
}

formula_t remove_clauses_containing(formula_t formula, literal_e literal) {
    bool contains = false;
    formula_t new_formula = {};

    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            if (formula[i][j] == literal) { contains = true; }
        }

        if (contains) {}
        else { new_formula.push_back(formula[i]); }

        contains = false;
    }

    return new_formula;
}
            

formula_t apply_pure_lit_rule(formula_t formula) {
     
    literal_e lits[8]      = {w,     x,     y,     z,     nw,    nx,    ny,    nz   };
    bool contains[8] = {false, false, false, false, false, false, false, false};
    
    for(int i = 0; i < formula.size(); ++i) {
        for(int j = 0; j < formula[i].size(); ++j) {
            switch(formula[i][j]) {
            case w:
                contains[0] = true;
                break;
            case x:
                contains[1] = true;
                break;
            case y:
                contains[2] = true;
                break;
            case z:
                contains[3] = true;
                break;
            case nw:
                contains[4] = true;
                break;
            case nx:
                contains[5] = true;
                break;
            case ny:
                contains[6] = true;
                break;
            case nz:
                contains[7] = true;
                break;
            default:
                return {};
            }
        }
    }

    for(int i = 0; i < 4; ++i) {
        if (contains[i] && !contains[i+4])      { formula = remove_clauses_containing(formula, lits[i]); }
        else if (!contains[i] && contains[i+4]) { formula = remove_clauses_containing(formula, lits[i+4]); }
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
