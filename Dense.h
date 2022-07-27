#ifndef C___PROJECT_DENSE_H
#define C___PROJECT_DENSE_H

#include "Activation.h"
#include "Matrix.h"
// implement class Dense here...
class Dense{
private:
    Matrix _weight;
    Matrix _bias;
    Activation _act;
public:
    //constructor
    Dense(const Matrix& w, const Matrix& bias, const Activation& act_type);
    //getters
    Matrix get_weights()const;
    Matrix get_bias()const;
    Activation get_activation()const;
    //() operator
    Matrix operator()(const Matrix& x) const;

};

#endif //C___PROJECT_DENSE_H
