#ifndef SAT_H
#define SAT_H

#include <string>
#include <vector>

enum variable { w, x, y, z, inv };

/* Decleration of the formula */
typedef struct literal { 
    bool is_neg;
    variable var;
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

void show_literal(literal_t literal); 

formula_t make_formula(expression_t exp);

/* The DPLL algorithm */
bool DPLL(formula_t exp);

bool is_pure(variable v, bool nval, formula_t formula);

std::vector<clause_t> apply_1_lit_rule(literal_t u, std::vector<clause_t> formula); 

bool contains_trivially_unsat(formula_t formula); 

bool is_consistent_set_of_literals(formula_t form);

bool contains_empty_clause(formula_t form);

#endif
