//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H


#include <iostream>
#include "Matrix.h"
#include "Dense.h"
#include "Digit.h"


#define MLP_SIZE 4

//
const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64, 128},
                                    {20, 64},
                                    {10, 20}};
const matrix_dims bias_dims[]    = {{128, 1},
                                    {64, 1},
                                    {20, 1},
                                    {10, 1}};

// Insert MlpNetwork class here...
class MlpNetwork{
private:
    Dense _r1;
    Dense _r2;
    Dense _r3;
    Dense _r4;
public:
    //constructor
    MlpNetwork(const Matrix weights[], const Matrix biases[]);
    //() operator
    Digit operator()(const Matrix& x) const;
};

#endif // MLPNETWORK_H
