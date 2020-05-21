#ifndef SAT_H
#define SAT_H

#include <string>
#include <vector>


/* Decleration of the formula */
typedef struct literal { 
    bool is_neg;
    enum var { w, x, y, z };
} literal_t;

typedef std::vector<literal_t> clause_t;

typedef std::vector<clause_t> formula_t;

/* Decleration of the alphabet */
enum alphabet { var_w, var_x, var_y, var_z,
                neg, 
                open_par, close_par,
                comma,
                invalid };

typedef std::vector<alphabet> expression_t;

expression_t parse(std::string str_exp); 

formula_t make_formula(expression_t exp);

/* The DPLL algorithm */
bool DPLL(formula_t exp);

bool is_consistent_set_of_literals(formula_t form);

bool contains_empty_clause(formula_t form);

#endif
