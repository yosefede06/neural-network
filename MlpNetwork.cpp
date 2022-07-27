#include "MlpNetwork.h"

//constructor
MlpNetwork::MlpNetwork(const Matrix weights[],
                       const Matrix biases[]):
    _r1(weights[0], biases[0], RELU),
    _r2(weights[1], biases[1], RELU),
    _r3(weights[2], biases[2], RELU),
    _r4(weights[3], biases[3], SOFTMAX){
}

//() operator
Digit MlpNetwork::operator()(const Matrix &x) const{
    int max_ind = 0;
    Matrix mat_1(_r1(x));
    Matrix mat_2(_r2(mat_1));
    Matrix mat_3(_r3(mat_2));
    Matrix final_output(_r4(mat_3));
    for(int i = 0; i < final_output.get_cols() *final_output.get_rows(); i++){
        if(final_output[i] > final_output[max_ind]){
            max_ind = i;
        }
    }
    return Digit{(unsigned int)max_ind, final_output[max_ind]};
}

