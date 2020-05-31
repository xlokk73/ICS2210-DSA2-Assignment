#ifndef FORMULA_H
#define FORMULA_H

#include <string>
#include <vector>

enum literal_e { w, x, y, z, nw, nx, ny, nz, inv };

/* Decleration of the formula */

typedef std::vector<literal_e> clause_t;

typedef std::vector<clause_t> formula_t;

/* Decleration of the alphabet */
enum alphabet { var_w, var_x, var_y, var_z,
                neg, 
                open_par, close_par,
                comma,
                invalid };

typedef std::vector<alphabet> expression_t;

expression_t parse(std::string str_exp); 

void show_literal(literal_e literal); 

formula_t make_formula(expression_t exp);

void show_formula(formula_t formula);

#endif
