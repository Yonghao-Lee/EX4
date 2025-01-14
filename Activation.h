// Activation.h
#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"
#include <cmath>
#include <iostream>
// Insert Activation namespace here...
namespace Activation{

    typedef Matrix (*ActivationFunction)(const Matrix&);

    Matrix relu(const Matrix& input);
    Matrix softmax(const Matrix& input);
}








#endif //ACTIVATION_H