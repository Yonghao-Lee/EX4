#include "Dense.h"
#include <iostream>
#include <cmath>

Matrix Dense::operator()(const Matrix& input) const{
    Matrix weights_transposed = weights.transpose();
    Matrix biases_transposed = biases.transpose();

    Matrix result = input * weights_transposed + biases_transposed;

    return act(result);
}