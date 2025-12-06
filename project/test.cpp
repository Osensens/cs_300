#include <iostream>
#include "Matrix.h"
#include "Tensor3D.h"

using namespace std;

int main() {

    //  Test 1: Simple Matrix Addition 
    Matrix<int> A = {{0,0},{0,0}};
    Matrix<int> B = {{1,1},{1,1}};
    Matrix<int> C = A + B;

    cout << "Test 1: [0 0; 0 0] + [1 1; 1 1]\n";
    cout << "Expected: [1 1; 1 1]\n";
    cout << "Actual  : [" << C(0,0) << " " << C(0,1)
         << "; " << C(1,0) << " " << C(1,1) << "]\n\n";

    // Test 2: Transpose 
    Matrix<int> D = {{1,2,3},{4,5,6}};
    auto Dt = D.transpose();

    cout << "Test 2: Transpose of [1 2 3; 4 5 6]\n";
    cout << "Expected: [1 4; 2 5; 3 6]\n";
    cout << "Actual  : [" << Dt(0,0) << " " << Dt(0,1)
         << "; " << Dt(1,0) << " " << Dt(1,1)
         << "; " << Dt(2,0) << " " << Dt(2,1) << "]\n\n";

    // Test 3: Matrix Multiplication 
    Matrix<int> M1 = {{1,2},{3,4}};
    Matrix<int> M2 = {{5,6},{7,8}};
    auto M3 = M1 * M2;

    cout << "Test 3: Multiplication [1 2; 3 4] * [5 6; 7 8]\n";
    cout << "Expected: [19 22; 43 50]\n";
    cout << "Actual  : [" << M3(0,0) << " " << M3(0,1)
         << "; " << M3(1,0) << " " << M3(1,1) << "]\n\n";

    // Test 4: Invalid Matrix Addition 
    cout << "Test 4: Invalid Addition (2x2 + 3x3)\n";
    try {
        Matrix<int> X(2,2,0);
        Matrix<int> Y(3,3,0);
        auto Z = X + Y;
        cout << "ERROR: This should NOT have succeeded.\n\n";
    } catch (exception &e) {
        cout << "Correctly caught error: " << e.what() << "\n\n";
    }

    // Test 5: Tensor Construction and Access 
    Tensor3D<int> T = {
        { {1,2,3}, {4,5,6} },
        { {7,8,9}, {10,11,12} }
    };

    cout << "Test 5: Access T(1,1,2)\n";
    cout << "Expected: 12\n";
    cout << "Actual  : " << T(1,1,2) << "\n\n";

    //  Test 6: Tensor Slice 
    auto slice0 = T.slice(0);
    cout << "Test 6: Slice at depth 0\n";
    cout << "Expected: [1 2 3; 4 5 6]\n";
    cout << "Actual  : [" << slice0(0,0) << " "
         << slice0(0,1) << " "
         << slice0(0,2) << "; "
         << slice0(1,0) << " "
         << slice0(1,1) << " "
         << slice0(1,2) << "]\n\n";

    // Test 7: Tensor Addition 
    auto Tsum = T + T;
    cout << "Test 7: Tensor Addition (T + T)\n";
    cout << "Expected at (0,0,0): 2\n";
    cout << "Actual   at (0,0,0): " << Tsum(0,0,0) << "\n\n";

    //  Test 8: Tensor Elementwise Multiply 
    auto Tmul = T.elemwiseMultiply(T);
    cout << "Test 8: Tensor Elementwise Multiply\n";
    cout << "Expected at (0,0,0): 1\n";
    cout << "Actual   at (0,0,0): " << Tmul(0,0,0) << "\n\n";

    // Test 9: Tensor Reshape 
    T.reshape(3,2,2);
    cout << "Test 9: Reshape tensor to (3x2x2)\n";
    cout << "Expected last value: 12\n";
    cout << "Actual   last value: " << T(2,1,1) << "\n\n";

    // Test 10: Invalid Tensor Addition 
    cout << "Test 10: Invalid Tensor Addition\n";
    try {
        Tensor3D<int> Tbad(1,2,2);
        auto bad = T + Tbad;
        cout << "ERROR: This should NOT have succeeded.\n";
    } catch (exception &e) {
        cout << "Correctly caught error: " << e.what() << "\n";
    }

    return 0;
}
