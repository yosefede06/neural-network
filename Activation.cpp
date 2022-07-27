#include <iostream>
#include <cmath>
#include "Activation.h"

//constructor
Activation::Activation(ActivationType act_type){
    if(act_type == RELU || act_type == SOFTMAX){
        _act_type = act_type;
    }
    else{
        std::cerr << "Error: Illegal Activation Type" << std::endl;
        exit(EXIT_FAILURE);
    }
}

ActivationType Activation::get_activation_type()const{
    return _act_type;
}

Matrix Activation::operator()(const Matrix& matrix_1)const{
    Matrix final_mat(matrix_1);
    if(_act_type == RELU){
        for(int i = 0; i < matrix_1.get_rows(); i++){
            for(int j = 0; j < matrix_1.get_cols(); j++){
                if(matrix_1(i,j) >= 0){}
                else{
                    final_mat(i,j) = 0;
                }
            }
        }
    }

    if(_act_type == SOFTMAX){
        float count = 0;
        for(int i = 0; i < matrix_1.get_rows(); i++){
            for(int j = 0; j < matrix_1.get_cols(); j++){
                count += std::exp(matrix_1(i,j));
            }
        }
        for(int i = 0; i < matrix_1.get_rows(); i++){
            for(int j = 0; j < matrix_1.get_cols(); j++){
                final_mat(i,j) = ((1/count) * std::exp(matrix_1(i,j)));
            }
        }
    }
    return final_mat;
}

