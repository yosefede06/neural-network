#include <iostream>
#include <cmath>
#include "Dense.h"

//constructor
Dense::Dense(const Matrix& w, const Matrix& bias,
             const Activation& act_type):
_weight(w), _bias(bias), _act(act_type){
    if(w.get_rows() != bias.get_rows())
    {
        std::cerr << "Error: The number of rows needs to be equal "
                     "for both matrices" << std::endl;
        exit(EXIT_FAILURE);
    }
    if(bias.get_cols() != 1)
    {
        std::cerr << "Error: bias needs to be a vector" << std::endl;
        exit(EXIT_FAILURE);
    }
}

//getters
Matrix Dense::get_weights()const{return _weight;}
Matrix Dense::get_bias()const{return _bias;}
Activation Dense::get_activation()const{return _act;}

//() operator
Matrix Dense::operator()(const Matrix& x)const{
    if(x.get_cols() != 1 || x.get_rows() != _weight.get_cols())
    {
        std::cerr << "Error: input vector needs to be a vector"
                     "which size equals weight's matrix number"
                     "of columns" << std::endl;
        exit(EXIT_FAILURE);
    }
    return _act((_weight * x) + _bias);
}



