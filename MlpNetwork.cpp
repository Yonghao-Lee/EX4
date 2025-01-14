#include "MlpNetwork.h"
#include <iostream>

MlpNetwork::MlpNetwork(const Matrix weights[MLP_SIZE], const Matrix biases[MLP_SIZE])
: layers{Dense(weights[0], biases[0], Activation::relu),
         Dense(weights[1], biases[1], Activation::relu),
         Dense(weights[2], biases[2], Activation::relu),
         Dense(weights[3], biases[3], Activation::softmax)}{}

digit MlpNetwork::operator()(const Matrix &input) const {
    Matrix result = input;
    for (int i = 0; i < MLP_SIZE; i++) {
        result = layers[i](result);
    }
    digit output{};
    output.value = result.argmax();
    output.probability = result[result.argmax()];
    return output;
  }