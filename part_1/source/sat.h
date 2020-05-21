#ifndef SAT_H
#define SAT_H

#include <string>
#include <vector>

enum alphabet { var_w, var_x, var_y, var_z,
                neg, 
                open_par, close_par,
                comma,
                invalid };

std::vector<alphabet> parse(std::string exp); 

#endif
