// Matrix.h

#ifndef MATRIX_H
#define MATRIX_H
#include <fstream>
#define PRINT_NUM 0.1
/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

// Insert Matrix class here...
class Matrix{
private:
    //number of rows
        int _rows;
    //number of columns
        int _cols;
    //matrix
        float* _mat;
public:
    //constructor
        Matrix(int rows, int cols);
    //default constructor
        Matrix();
    //copy constructor
        Matrix(const Matrix& other);
    //destructor
        ~Matrix();
    //updates matrix method
//        void update_mat(int rows, int cols);
    //getters
        int get_rows() const;
        int get_cols() const;
//        float ** get_mat() const;
    //transpose matrix method
        Matrix& transpose();
    //vectorize matrix method
        Matrix& vectorize();
    //print matrix
        void plain_print() const;
    //scalar product method
        Matrix dot(const Matrix &mat_1) const;
    //norm method
        float norm() const;
    //read binary file
        friend void read_binary_file(std::istream& my_stream, Matrix& mat_1);
    //matrix addition operator
        Matrix operator+(const Matrix& mat_1) const;
    //assignment operator
        Matrix& operator=(const Matrix& mat_1);
    //matrix multiplication operator
        Matrix operator*(const Matrix& mat_1) const;
    //scalar multiplication operator on the right
        Matrix operator*(float c) const;
    //scalar multiplication operator on the left
    friend Matrix operator*(float c, const  Matrix& rhs);
    //matrix addition accumulation operator
        Matrix& operator+=(const Matrix& mat_1);
    //[] const operator
        float operator[](int i) const;
    //[] operator
        float& operator[](int i);
    //() const operator
        float operator()(int ind_i, int ind_j) const;
    //() operator
        float& operator()(int i, int j);
    //<< operator
        friend std::ostream& operator<<(std::ostream& s, const Matrix& mat_1);
};



#endif //MATRIX_H
