#include "Activation.h"
#include <cmath>
#include <iostream>


namespace Activation {
    Matrix relu(const Matrix& input){
    Matrix result(input.get_rows(), input.get_cols());
    for(int i{0}; i < input.get_rows(); ++i){
        for (int j{0}; j < input.get_cols(); ++j){
            result(i, j) = std::max(0.0f, input(i, j));
        }
    }
    return result;
    }

    Matrix softmax(const Matrix& input){

      Matrix result(input.get_rows(), input.get_cols());
      float sum = 0.0f;
      for(int i{0}; i < input.get_rows(); ++i){
            for(int j{0}; j < input.get_cols(); ++j){
                result(i, j) = std::exp(input(i, j));
                sum += result(i, j);
            }
        }
        float coefficient = 1.0f / sum;
        for(int i{0}; i < input.get_rows(); ++i){
            for(int j{0}; j < input.get_cols(); ++j){
                result(i, j) *= coefficient;
            }
        }
        if (std::abs(sum) < 1e-6) {
            throw std::runtime_error("Softmax computation failed: sum of exponents is zero.");
        }
        return result;
      }

}
