//Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H
#include "Matrix.h"
/**
 * @enum ActivationType
 * @brief Indicator of activation function.
 */
enum ActivationType
{
    RELU,
    SOFTMAX
};

// Insert Activation class here...
class Activation{
private:
    ActivationType _act_type;
public:
    //constructor
    Activation(ActivationType act_type);
    //getter
    ActivationType get_activation_type()const;
    //() operator
    Matrix operator()(const Matrix& matrix_1)const;
};
#endif //ACTIVATION_H
