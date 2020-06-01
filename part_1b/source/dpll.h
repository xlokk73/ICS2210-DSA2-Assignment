#ifndef DPLL_H
#define DPLL_H

#include "formula.h"

/* The DPLL algorithm */
bool DPLL(formula_t exp);

formula_t remove_trivially_sat(formula_t formula); 

bool contains_trivially_unsat(formula_t formula); 
 


#endif
