#ifndef MATRIX_H
#define MATRIX_H

#include <vector>              // std::vector used for storage
#include <initializer_list>   // allow initializer_list constructor
#include <stdexcept>          // exceptions: out_of_range, runtime_error

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data; // 2D storage: data[row][col]
    size_t rows, cols;                // track dimensions

public:
    // Constructor with size and initial value
    Matrix(size_t r, size_t c, T init = T())
        : data(r, std::vector<T>(c, init)), // create r vectors each of size c filled with init
          rows(r), cols(c)                   // set member dimensions
    {
        // constructor body empty because initialization list did the work
    }

    // Initializer list constructor (for Matrix<int> A = {{1,2},{3,4}};)
    Matrix(std::initializer_list<std::initializer_list<T>> vals) {
        rows = vals.size();                      // number of depth elements in initializer_list = number of rows
        cols = (rows > 0) ? vals.begin()->size() : 0; // columns inferred from first row (if any)

        // Reserve/construct the data row-by-row
        for (auto& row : vals) {
            if (row.size() != cols) // ensure every row has same number of columns
                throw std::runtime_error("All rows must have same size");
            data.push_back(std::vector<T>(row)); // convert initializer_list row to std::vector<T> and append
        }
    }

    // Mutable element access with bounds checking
    T& operator()(size_t i, size_t j) {
        if (i >= rows || j >= cols)               // check indices
            throw std::out_of_range("Matrix index out of range");
        return data[i][j];                        // return reference so caller can modify
    }

    // Const element access
    const T& operator()(size_t i, size_t j) const {
        if (i >= rows || j >= cols)
            throw std::out_of_range("Matrix index out of range");
        return data[i][j];                        // return const ref for read-only contexts
    }

    // Simple dimension getters
    size_t numRows() const { return rows; }
    size_t numCols() const { return cols; }

    // Matrix addition: elementwise (this + other) -> new matrix
    Matrix<T> operator+(const Matrix<T>& other) const {
        if (rows != other.rows || cols != other.cols) // dimension check
            throw std::runtime_error("Matrix sizes do not match for addition");

        Matrix<T> result(rows, cols, T()); // create output initialized to default T()
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                result(i, j) = data[i][j] + other(i, j); // elementwise sum

        return result; // return by value (RVO/NRVO allows efficient return)
    }

    // Matrix multiplication: standard row*col algorithm
    Matrix<T> operator*(const Matrix<T>& other) const {
        if (cols != other.rows) // check inner-dimension compatibility
            throw std::runtime_error("Matrix sizes do not match for multiplication");

        Matrix<T> result(rows, other.cols, T()); // output is rows x other.cols, initialize with zero-like T()
        // Use i-k-j ordering to allow reuse of left element data[i][k]
        for (size_t i = 0; i < rows; i++) {
            for (size_t k = 0; k < cols; k++) {
                // Save a = data[i][k] to avoid repeated indexing and help readability
                T a = data[i][k];
                for (size_t j = 0; j < other.cols; j++) {
                    // Accumulate product into result(i,j)
                    result(i, j) += a * other(k, j);
                }
            }
        }

        return result;
    }

    // Transpose: rows <-> cols
    Matrix<T> transpose() const {
        Matrix<T> result(cols, rows, T()); // swapped dimensions
        for (size_t i = 0; i < rows; i++)
            for (size_t j = 0; j < cols; j++)
                result(j, i) = data[i][j]; // set transposed element

        return result;
    }
};

#endif
