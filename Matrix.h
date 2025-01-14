// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
// You don't have to use the struct. Can help you with MlpNetwork.h
struct matrix_dims
{
    int rows, cols;
};


// Insert Matrix class here...
class Matrix
{
private:
    int rows;
    int cols;
    float* data; // implementing it as a single col vector
public:
    Matrix(int rows, int cols); // constructor with params
    Matrix(); // default constructor
    Matrix(const Matrix& m); // copy constructor
    ~Matrix(); // destructor

    //Getters
    [[nodiscard]] int get_rows() const;
    [[nodiscard]] int get_cols() const;
    // elementary operations
    // swap for copy-swap
    void swap(Matrix& other) noexcept;

    // // swap rows i and j
    void swap_rows(int i, int j);
    // multiply row i by c
    void scale_row(int i, float c);
    // add c times row j to row i
    void add_row(int i, int j, float c);
    void check_index_bounds(int i, int j) const;

    // transpose, (A.transpose())_{i,j} = A_{j,i}
    [[nodiscard]] Matrix transpose() const;

    //vectorize the matrix transforms the matrix into a col vector
    // this supports chaining use *this
    void vectorize() ;

    // prints matrix elems, no return value
    // this prints space after each element including the last elem in the row
    // it prints the newline after each row
    void plain_print() const;

    // return a new mat that is the elem-wise multiplication(Hadamard product)
    // of this matrix with another matrix m:
    Matrix dot(const Matrix& m) const;
    // returns the norm of the given matrix
    [[nodiscard]] float norm() const;

    // returns a new matrix that is the rre form of the original
    //  is not changed
    [[nodiscard]] Matrix rref() const;


    // returns the index of the largest num in the matrix
    // in the case of a tie, return the lower index
    // possibly used to return the index of the final number with the probability
    [[nodiscard]] int argmax() const;

    // returns the sum of all elems in the mat
    [[nodiscard]] float sum() const;

    // operator overloading
    // += operator Mat addition
    Matrix& operator+=(const Matrix& m);
    // + matrix addition a, b -> a + b
    Matrix operator+(const Matrix& m) const;
    // = assignment
    Matrix& operator=(Matrix m);
    // * mat multiplication a, b -> a * b
    Matrix operator*(const Matrix& m) const;
    //  * scalar mult on the right matrix: m; float c; -> m * c
    Matrix operator*(float c) const;
    // () parenthesis operator, returns the element at the given index
    // m(1,3) = 10; float x = m(1,3) that is x equals 10.0
    float& operator()(int i, int j);
    const float& operator()(int i, int j) const;
    // brackets indexing: if m is an i row j col mat then m has i*j cells
    // for every 0 <= k < i*j, m[k] will return the kth element of the matrix
    // which is as if m is represented as a col vector
    // m(5,4); m[3] = 10; float x = m[3] // x = 10
    float& operator[](int k);
    const float& operator[](int i) const;
    // output stream
    friend std::ostream& operator<<(std::ostream& os, const Matrix& m);
    // input stream fills the mat elems, don't trust the user to validate it
    // the stream must have enough data to fill the matr all the way, if too short, throw and error
    friend std::istream& operator>>(std::istream& is, Matrix& m);
};


#endif //MATRIX_H
