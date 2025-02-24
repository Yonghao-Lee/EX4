// Dense.h
#ifndef DENSE_H
#define DENSE_H
#include "Matrix.h"
#include <iostream>
#include "Activation.h"

// Insert Dense class here...

class Dense
{
private:
    const Matrix& weights;
    const Matrix& biases;
    activation::ActivationFunction act;
public:
  Dense(const Matrix& weights, const Matrix& biases, activation::ActivationFunction act)
      : weights{weights}, biases{biases}, act{act}{};
  // getters
    const Matrix& get_weights() const { return weights; }
    const Matrix& get_bias() const { return biases; }
    activation::ActivationFunction get_activation() const { return act; }

    // operator overloading
    Matrix operator()(const Matrix& input) const;

};








#endif //DENSE_H