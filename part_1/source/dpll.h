#ifndef DPLL_H
#define DPLL_H

#include "formula.h"

/* The DPLL algorithm */
bool DPLL(formula_t exp);

formula_t remove_trivially_sat(formula_t formula); 

bool contains_trivially_unsat(formula_t formula); 
 
formula_t apply_1_lit_rule(literal_e u, formula_t formula);

bool contains_empty_clause(formula_t formula);

formula_t apply_pure_lit_rule(formula_t formula);

literal_e choose_literal(formula_t formula);

literal_e negate(literal_e literal);

#endif
