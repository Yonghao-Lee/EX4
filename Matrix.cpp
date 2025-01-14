#include <iostream>
#include <cmath>
#include <fstream>
#include "Matrix.h"



// constructor with params
Matrix::Matrix(int rows, int cols) : rows(rows), cols(cols)
{
    if (rows <= 0 || cols <= 0)
    {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    data = new float[rows * cols];
    std::fill_n(data, rows * cols, 0.0f);
}

// default constructor
Matrix::Matrix(): Matrix(1, 1)
{
}

// copy constructor
Matrix::Matrix(const Matrix& m): rows(m.rows), cols(m.cols), data{new float[rows * cols]}
{
std::copy(m.data, m.data + rows * cols, data);}

// destructor
Matrix::~Matrix()
{
    delete[] data;
}

//Getters
int Matrix::get_rows() const { return rows; }
int Matrix::get_cols() const { return cols; }

// transpose the matrix
Matrix Matrix::transpose() const
{


    Matrix result(cols, rows);
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < cols; ++j)
        {
            result(j, i) = (*this)(i, j);
        }
}
    return result;
}

//vectorize the matrix transforms the matrix into a col vector
// this supports chaining use *this
Matrix Matrix::vectorize() const
{
    Matrix result(1, rows * cols);
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < cols; ++j)
        {
            result(0, i * cols + j) = (*this)(i, j);
        }
    }
    return result;
}
// for all i,j (A.dot(B)_{ij} = A_{ij} * B_{ij})
Matrix Matrix::dot(const Matrix& m) const
{
    if (rows != m.rows || cols != m.cols)
    {
        throw std::invalid_argument("Matrix dimensions do not match in dot");
    }

    Matrix result(rows, cols);
    for (int i{0}; i < rows * cols; ++i)
    {
        result.data[i] = data[i] * m.data[i];
    }
    return result;
}
// prints matrix elems, no return value
// this prints space after each element including the last elem in the row
// it prints the newline after each row
void Matrix::plain_print() const
{
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < cols; ++j)
        {
            std::cout << (*this)(i, j) << " ";
        }
        std::cout << "\n";
    }
}

// returns the norm of the given matrix
float Matrix::norm() const
{
    float result{};
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < cols; ++j)
        {
            result += (*this)(i, j) * (*this)(i, j);
        }
    }
    result = std::sqrt(result);
    return result;
}

void Matrix::check_index_bounds(int i, int j) const
{
    if (i < 0 || i >= rows || j < 0 || j >= cols)
    {
        throw std::out_of_range("Index out of range in check_index_bounds");
    }
}

// elementary operations for matrix
// swap rows i and j
void Matrix::swap_rows(int i, int j)
{
    check_index_bounds(i, j);
    if (i == j)
    {
        // No need to swap a row with itself
        return;
    }
    for (int k{0}; k < cols; ++k)
    {
        std::swap((*this)(i, k), (*this)(j, k));
    }
}

// multiply row i by c
void Matrix::scale_row(int i, float c)
{
    check_index_bounds(i, 0);
    if (rows == 0 || cols == 0)
    {
        throw std::logic_error("Cannot scale a row in an empty matrix");
    }
    if (c == 0)
    {
        throw std::invalid_argument("Scaling factor cannot be zero in scale_row");
    }
    for (int k{0}; k < cols; ++k)
    {
        (*this)(i, k) *= c;
    }
}

// add c times row j to row i
void Matrix::add_row(int i, int j, float c)
{
    check_index_bounds(i, 0);
    check_index_bounds(j, 0);
    if (rows == 0 || cols == 0)
    {
        throw std::logic_error("Cannot add rows in an empty matrix");
    }
    if (c == 0)
    {
        return;
    }
    if (i == j)
    {
        throw std::invalid_argument("Cannot add a row to itself in add_row");
    }
    for (int k{0}; k < cols; ++k)
    {
        (*this)(i, k) += c * (*this)(j, k);
    }
}

// returns a new matrix that is the rre form of the original
//  is not changed
Matrix Matrix::rref() const
{
    Matrix result(*this);
    int lead = 0; // current pivot col;

    for (int r = 0; r < result.get_rows(); ++r)
    {
        if (result.get_cols() <= lead)
        {
            break;
        }

        int i = r;
        while (i < result.get_rows() && std::abs(result(i, lead)) < 1e-6)
        {
            i++;
        }
        if (i == result.get_rows())
        {
            // no pivot in this column, move on
            lead++;
            r--;
            continue;
        }

        // swap the current row with the pivot row
        result.swap_rows(i, r);

        // normalize the pivot row
        const float pivot = result(r, lead);
        if (std::abs(pivot) > 1e-6) {
            result.scale_row(r, 1.0f / pivot);
        }

        // eliminate all the rest entries in the pivot col
        for (int j{0}; j < result.get_rows(); ++j)
        {
            if (j != r)
            {
                const float factor = result(j, lead);
                result.add_row(j, r, -factor);
            }
        }
        lead++;
    }
    return result;
}

// returns the index of the largest num in the matrix
// in the case of a tie, return the lower index
// possibly used to return the index of the final number with the probability
int Matrix::argmax() const
{
    if (rows == 0 || cols == 0)
    {
        throw std::runtime_error("Matrix is empty. Cannot compute argmax.");
    }
    int max_index = 0;
    for (int i = 1; i < rows * cols; ++i)
    {
        if (data[i] > data[max_index])
        {
            max_index = i;
        }
    }
    return max_index;
}

// returns the sum of all elems in the mat
[[nodiscard]] float Matrix::sum() const
{
    float result{};
    for (int i{0}; i < rows * cols; ++i)
    {
        result += data[i];
    }
    return result;
}

// operator overloading
// += operator Mat addition
Matrix& Matrix::operator+=(const Matrix& m)
{
    if (rows != m.rows || cols != m.cols)
    {
        throw std::invalid_argument("Matrix dimensions do not match in operator +=");
    }

    for (int i{0}; i < rows * cols; ++i)
    {
        if (i >= m.rows * m.cols) // Debug for out-of-bounds error
        {
            throw std::out_of_range("Out of bounds in operator +=");
        }
        data[i] += m.data[i];
    }
    return *this;
}

// + matrix addition a, b -> a + b
Matrix Matrix::operator+(const Matrix& m) const
{
    if (rows != m.rows || cols != m.cols)
    {
        throw std::invalid_argument("Matrix dimensions do not match in operator+.");
    }
    Matrix result{*this};
    result += m;
    return result;
}

void Matrix::swap(Matrix& other) noexcept
{
    std::swap(rows, other.rows);
    std::swap(cols, other.cols);
    std::swap(data, other.data);
}

// = assignment
Matrix& Matrix::operator=(Matrix m)
{
    swap(m);
    return *this;
}

// * mat multiplication a, b -> a * b
Matrix Matrix::operator*(const Matrix& m) const
{
    if (cols != m.rows) {
        throw std::invalid_argument("Matrix multiplication dimension mismatch");
    }

    Matrix result(rows, m.cols);
    for (int i{0}; i < rows; ++i)
    {
        for (int j{0}; j < m.cols; ++j)
        {
            float sum = 0;
            for (int k{0}; k < cols; ++k)
            {
                sum += (*this)(i, k) * m(k, j);
            }
            result(i, j) = sum;
        }
    }
    return result;
}

//  * scalar mult on the right matrix: m; float c; -> m * c
Matrix Matrix::operator*(float c) const
{
    Matrix result{*this};
    for (int i{0}; i < rows * cols; ++i)
    {
        result.data[i] *= c;
    }
    return result;
}

// () parenthesis operator, returns the element at the given index
// m(1,3) = 10; float x = m(1,3) that is x equals 10.0
float& Matrix::operator()(int i, int j)
{
    check_index_bounds(i, j);

    return data[i * cols + j];
}

const float& Matrix::operator()(int i, int j) const
{
  check_index_bounds(i, j);
    return data[i * cols + j];
}

// brackets indexing: if m is an i row j col mat then m has i*j cells
// for every 0 <= k < i*j, m[k] will return the kth element of the matrix
// which is as if m is represented as a col vector
// m(5,4); m[3] = 10; float x = m[3] // x = 10
float& Matrix::operator[](int k)
{
    if (k < 0 || k >= rows * cols)
    {
        throw std::out_of_range("Index out of range in operator[]");
    }
    return data[k];
}

// Overloaded operator[] for const objects
const float& Matrix::operator[](int k) const
{
    if (k < 0 || k >= rows * cols)
    {
        throw std::out_of_range("Index out of range in operator[]");
    }
    return data[k];
}

// output stream
std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    for (int i{0}; i < m.rows; ++i)
    {
        for (int j{0}; j < m.cols; ++j)
        {
            if (m(i, j) > 0.1)
            {
                os <<  "**";
            }
            else
            {
                os << "  ";
            }
        }
        os << "\n";
    }
    return os;
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    for (int i = 0; i < m.rows; ++i)
    {
        for (int j = 0; j < m.cols; ++j)
        {
            // Read element
            if (!(is >> m(i, j)))
            {
                // If reading fails, throw an error
                throw std::runtime_error("Insufficient or invalid input to fill the matrix");
            }
        }
    }
    return is;
}
