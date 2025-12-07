#ifndef TENSOR3D_H
#define TENSOR3D_H

#include <vector>
#include <initializer_list>
#include <stdexcept>
#include "Matrix.h" 

template <typename T>
class Tensor3D {
private:
    // 3D storage: data[depth][row][col]
    std::vector<std::vector<std::vector<T>>> data;
    size_t depth, rows, cols; // dimensions

public:
    // Constructor with dimensions and initial fill value
    Tensor3D(size_t d, size_t r, size_t c, T init = T())
        : data(d, std::vector<std::vector<T>>(r, std::vector<T>(c, init))),
          depth(d), rows(r), cols(c)
    {
        // initialization list constructs the nested vectors
    }

    // Initializer list constructor 
    Tensor3D(std::initializer_list<std::initializer_list<std::initializer_list<T>>> vals) {
        depth = vals.size();       // number of slices
        if (depth == 0) { rows = cols = 0; return; }   // empty tensor edge-case

        // infer rows and cols from first slice
        rows = vals.begin()->size();
        cols = (rows > 0) ? vals.begin()->begin()->size() : 0;

        data.reserve(depth); // reserve capacity for depth slices
        // build each slice
        for (auto &slice : vals) {
            if (slice.size() != rows) // all slices must have same number of rows
                throw std::runtime_error("Inconsistent rows across slices");
            std::vector<std::vector<T>> mat; // temporary 2D matrix for the slice
            mat.reserve(rows);
            for (auto &row : slice) {
                if (row.size() != cols) // each row must have same number of cols
                    throw std::runtime_error("Inconsistent cols across rows");
                mat.emplace_back(row); // convert initializer_list row to vector<T> and append
            }
            data.emplace_back(std::move(mat)); // append this slice
        }
    }

    // Mutable element access with bounds checks
    T& operator()(size_t k, size_t i, size_t j) {
        if (k >= depth || i >= rows || j >= cols)
            throw std::out_of_range("Tensor3D index out of range");
        return data[k][i][j];
    }

    // Const element access
    const T& operator()(size_t k, size_t i, size_t j) const {
        if (k >= depth || i >= rows || j >= cols)
            throw std::out_of_range("Tensor3D index out of range");
        return data[k][i][j];
    }

    // Dimension getters
    size_t getDepth() const { return depth; }
    size_t numRows() const { return rows; }
    size_t numCols() const { return cols; }

    // Elementwise addition
    Tensor3D<T> operator+(const Tensor3D<T>& other) const {
        if (depth != other.depth || rows != other.rows || cols != other.cols)
            throw std::runtime_error("Shape mismatch for addition");
        Tensor3D<T> out(depth, rows, cols);
        for (size_t k = 0; k < depth; ++k)
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < cols; ++j)
                    out(k,i,j) = data[k][i][j] + other(k,i,j);
        return out;
    }

    // Elementwise multiplication
    Tensor3D<T> elemwiseMultiply(const Tensor3D<T>& other) const {
        if (depth != other.depth || rows != other.rows || cols != other.cols)
            throw std::runtime_error("Shape mismatch for elemwise multiply");
        Tensor3D<T> out(depth, rows, cols);
        for (size_t k = 0; k < depth; ++k)
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < cols; ++j)
                    out(k,i,j) = data[k][i][j] * other(k,i,j);
        return out;
    }

    // Return k-th depth slice as a Matrix<T>
    Matrix<T> slice(size_t k) const {
        if (k >= depth)
            throw std::out_of_range("Slice index out of range");
        Matrix<T> M(rows, cols); // construct matrix with same rows/cols
        for (size_t i = 0; i < rows; ++i)
            for (size_t j = 0; j < cols; ++j)
                M(i,j) = data[k][i][j]; // copy values into matrix
        return M; // return slice by value
    }

    // Reshape tensor in-place while preserving element order
    void reshape(size_t newD, size_t newR, size_t newC) {
        size_t total_old = depth * rows * cols;        // total elements now
        size_t total_new = newD * newR * newC;         // total elements after reshape
        if (total_old != total_new)
            throw std::runtime_error("Total size must remain same for reshape");

        // Flatten current data into 1D vector (depth-major, then row, then col)
        std::vector<T> flat;
        flat.reserve(total_old);
        for (size_t k = 0; k < depth; ++k)
            for (size_t i = 0; i < rows; ++i)
                for (size_t j = 0; j < cols; ++j)
                    flat.push_back(data[k][i][j]);

        // Rebuild nested vectors with new dimensions and refill from flat preserving order
        data.clear();
        data.resize(newD, std::vector<std::vector<T>>(newR, std::vector<T>(newC)));
        size_t idx = 0;
        for (size_t k = 0; k < newD; ++k)
            for (size_t i = 0; i < newR; ++i)
                for (size_t j = 0; j < newC; ++j)
                    data[k][i][j] = flat[idx++];

        // Update metadata
        depth = newD; rows = newR; cols = newC;
    }

    // Channel-wise multiplication with a matrix M (C x K) producing (D x R x K)
    Tensor3D<T> operator*(const Matrix<T>& M) const {
        if (cols != M.numRows())
            throw std::runtime_error("Matrix columns must match tensor cols for channel-wise multiplication");

        size_t K = M.numCols();
        Tensor3D<T> out(depth, rows, K, T()); // result has K columns
        for (size_t k = 0; k < depth; ++k) {
            // For each depth slice treat it as an (R x C) matrix and multiply by M (C x K)
            for (size_t i = 0; i < rows; ++i) {
                for (size_t c = 0; c < cols; ++c) {
                    T a = data[k][i][c]; // element in slice row i column c
                    for (size_t j = 0; j < K; ++j) {
                        // accumulate a * M(c,j) into out(k,i,j)
                        out(k,i,j) += a * M(c,j);
                    }
                }
            }
        }
        return out;
    }
};

#endif
