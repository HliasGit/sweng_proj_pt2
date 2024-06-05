#include "matrix_multiplication.h"
#include <iostream>
#include <vector>
#include <gtest/gtest.h>

// ######################### Source code of multiplyMatrices in src/matrix_mult

TEST(MatrixMultiplicationTest, TestMultiplyMatrices) {
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}
    };
    std::vector<std::vector<int>> B = {
        {7, 8},
        {9, 10},
        {11, 12}
    };

    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 3, 2);

    std::vector<std::vector<int>> expected = {
        {58, 64},
        {139, 154}
    };

    ASSERT_EQ(C, expected) << "Matrix multiplication test failed! :(((((";
}


/*
When multiplying a matrix times a matrix with all entries to zero we expect a zero matrix
*/
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_zeroMatrixRight)
{
    std::vector<std::vector<int>> A = {
        {1, 2, 3},
        {4, 5, 6}};
    std::vector<std::vector<int>> B = {
        {0, 0},
        {0, 0},
        {0, 0}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> C2(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 3, 2);
    std::vector<std::vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    ASSERT_EQ(C, expected) << "Matrix multiplication by zero on the right test failed! :(((()";
}

/*
When multiplying a zero matrix times a generic matrix we expect a zero matrix.
It's different from the previuous test case since the matrix multiplication is not commutative
*/
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_zeroMatrixLeft)
{
    std::vector<std::vector<int>> A = {
        {0, 0, 0},
        {0, 0, 0}};
    std::vector<std::vector<int>> B = {
        {1, 2},
        {3, 4},
        {5, 6}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 3, 2);
    std::vector<std::vector<int>> expected = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    ASSERT_EQ(C, expected) << "Matrix multiplication by zero on the right test failed! :(((()";
}

/*
A generic matrix times the identity matrix gives back the original generic matrix
*/
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_identityMatrixRight)
{
    std::vector<std::vector<int>> A = {
        {1, 2},
        {4, 5}};
    std::vector<std::vector<int>> B = {
        {1, 0},
        {0, 1}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    std::vector<std::vector<int>> expected = {
        {1, 2},
        {4, 5}};

    multiplyMatrices(A, B, C, 2, 2, 2);

    ASSERT_EQ(C, expected) << "Matrix multiplication by the identity on the right test failed! :(((()";
}

/*
The identity matrix times a generic matrix gives back the original generic matrix
It's different from the previuous test case since the matrix multiplication is not commutative
*/
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_identityMatrixLeft)
{
    std::vector<std::vector<int>> A = {
        {1, 0},
        {0, 1}};
    std::vector<std::vector<int>> B = {
        {1, 2},
        {4, 5}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    std::vector<std::vector<int>> expected = {
        {1, 2},
        {4, 5}};

    multiplyMatrices(A, B, C, 2, 2, 2);

    ASSERT_EQ(C, expected) << "Matrix multiplication by the identity on the left test failed! :(((()";
}

/*
A matrix mutliplied by itself gives the squared matrix
*/
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_squaredMatrix)
{
    std::vector<std::vector<int>> A = {
        {5, 0},
        {0, 5}};
    std::vector<std::vector<int>> B = {
        {5, 0},
        {0, 5}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));
    
    multiplyMatrices(A, B, C, 2, 2, 2);

    std::vector<std::vector<int>> expected = {
        {25, 0},
        {0, 25}};

    ASSERT_EQ(C, expected) << "Matrix multiplication by itself test failed! :(((()";
}

/*
Test that the matrix times its inverse gives the identity
*/
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_matrixTimesInverseMatrix)
{
    std::vector<std::vector<int>> A = {
        {2, 1},
        {1, 1}};
    std::vector<std::vector<int>> B = {
        {1, -1},
        {-1, 2}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 2, 2);

    std::vector<std::vector<int>> expected = {
        {1, 0},
        {0, 1}};

    ASSERT_EQ(C, expected) << "Matrix multiplication by its inverse test failed! :(((()";
}

/*
Test associativity property:
A(BC)=(AB)C

First muliply B and C, store it in D_one after multiplying it with A.
Do the same for A and B, then in D_two after multiplying with C
Assert that they are the same
*/
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_associativity)
{
    std::vector<std::vector<int>> A = {
        {1, 2},
        {3, 4}};
    std::vector<std::vector<int>> B = {
        {5, 6},
        {7, 8}};
    std::vector<std::vector<int>> C = {
        {9, 10},
        {11, 12}};
    std::vector<std::vector<int>> temp(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D_one(2, std::vector<int>(2, 0));
    std::vector<std::vector<int>> D_two(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, temp, 2, 2, 2);
    multiplyMatrices(temp, C, D_one, 2, 2, 2);

    multiplyMatrices(B, C, temp, 2, 2, 2);
    multiplyMatrices(A, temp, D_two, 2, 2, 2);

    ASSERT_EQ(D_one, D_two) << "Matrix associativity property test failed! :(((()";
}

/*
Iterate brute force. We exploited this brute force method just to retrieve
all the 20 errors we had to find, since some of them are quite brainy and can't be found through logical reasoning
This test has not been reported in the correct implementation because it is not possible to know the result a priori
*/

// We should also test that the dimensions of the matrices are compatible, i.e. that the number of columns of the first
// matrix are the same as the number of rows of the second matrix. Though the program doesn't perform this check, so it doesn't
// make sense. Same reasoning for a test checking that the matrix dimensions are not negative.

// an implementation of the aformeentioned test about dimension compatibility is the one below, though it should expect a custom
// error (i.e. invalid matrix dimensions, which is not implemented in the multiplyMatrices method) and not a standard out of range
TEST(MatrixMultiplicationTest, TestMultiplyMatrices_squaredMatrix)
{
    std::vector<std::vector<int>> A = {
        {5, 0},
        {0, 5},
        {0, 1}};
    std::vector<std::vector<int>> B = {
        {5, 0},
        {0, 5}};
    std::vector<std::vector<int>> C(2, std::vector<int>(2, 0));

    multiplyMatrices(A, B, C, 2, 2, 2);

    EXPECT_THROW(multiplyMatrices(A, B), std::out_of_range);
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}