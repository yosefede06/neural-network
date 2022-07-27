#include <iostream>
#include <cmath>
#include "Matrix.h"

////updates matrix method
//void Matrix::update_mat(int rows, int cols){
//    //Deletes the old matrix memory allocation
//    for(int i=0; i < _rows; i++){
//        delete _mat[i];
//    }
//    delete[] _mat;
//    //Allocates new memory with the new sizes
//    _rows = rows;
//    _cols = cols;
//    _mat = new float*[rows];
//    for(int i = 0; i < rows; i++){
//        _mat[i] = new float[cols];
//        for(int j=0; j< cols; j++){
//            _mat[i][j] = 0;
//        }
//    }
//}



//constructor
Matrix::Matrix(int rows, int cols):
_rows(rows), _cols(cols){
    if(rows <= 0 || cols <= 0)
    {
        std::cerr << "Error: rows and columns"
                     " have to be"
                     " positive integers" << std::endl;
        exit(EXIT_FAILURE);
    }
    _mat = new float[cols*rows];
    for(int j = 0; j < cols*rows; j++){
        _mat[j]= 0;
    }
}

//default constructor
Matrix::Matrix(): Matrix(1, 1){
}

//copy constructor
Matrix::Matrix(const Matrix &new_mat):
_rows(new_mat._rows), _cols(new_mat._cols){
    int dim = new_mat._rows * new_mat._cols;
    _mat = new float[dim];
    for(int j = 0; j < dim; j++){
        _mat[j] = new_mat[j];
    }
}



//destructor
Matrix::~Matrix(){
    //deletes one dimensional matrix;
    delete[] _mat;
}

//getters
int Matrix::get_rows()const{return _rows;}
int Matrix::get_cols()const{return _cols;}

//transpose method
Matrix& Matrix::transpose(){
    Matrix mat_1(*this);
    _cols = mat_1.get_rows();
    _rows = mat_1.get_cols();
//    update_mat(_cols, _rows);
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols; j++){
            (*this)(i,j) = mat_1(j,i);
        }
    }
    return *this;
}

//vectorize method
Matrix& Matrix::vectorize(){
//    Matrix temp(*this);
//    update_mat(_rows * _cols,1);
//    int count = 0;
//    for(int i = 0; i < temp.get_rows(); i++){
//        for(int j = 0; j < temp.get_cols(); j++){
//            _mat[count][0] = temp(i,j);
//            count ++;
//        }
//    }
//    return *this;
    _rows = _cols * _rows ;
    _cols = 1;
    return *this;
}

//print matrix method
void Matrix::plain_print()const{
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols; j++){
            std::cout << (*this)(i,j) << " ";
        }
        std::cout << std::endl;
    }
}

//dot matrix method
Matrix Matrix::dot(const Matrix &mat_1)const{
    if(mat_1.get_cols() != _cols
    || mat_1.get_rows() != _rows){
        std::cerr << "Error: Matrices of "
                     "different sizes"
                     " can not be dot "
                     "multiplied." << std::endl;
        exit(EXIT_FAILURE);
    }
    Matrix final(_rows, _cols);
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols ; j++){
        //final(i,j): calls
        // non const () operator,
        // which returns reference
        // of element on index (i,j)
        final(i,j) = (*this)(i,j) * mat_1(i,j);
        }
    }
    return final;
}

//norm matrix method
float Matrix::norm()const{
    float curr_result = 0;
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols; j++){
            curr_result += (*this)(i,j) * (*this)(i,j);
        }
    }
    return sqrt(curr_result);
}

//read binary file
void read_binary_file(std::istream &my_stream,
                      Matrix &mat_1)
{
    my_stream.seekg(0, std::ios::end);
    int my_size = my_stream.tellg();
    my_stream.seekg(0, std::ios::beg);
    my_stream.read ((char*)mat_1._mat, my_size);
    if (my_stream.fail() || my_stream.eof()){
        std::cerr << "Error: not readable"
                     " or not complete" << std::endl;
        exit(EXIT_FAILURE);
    }
}

//matrix addition operator
Matrix Matrix::operator+(const Matrix& mat_1)const{
    if(mat_1.get_cols() != _cols ||
    mat_1.get_rows() != _rows){
        std::cerr << "Error: Matrices of"
                     " different sizes"
                     " can not be added." << std::endl;
        exit(EXIT_FAILURE);
    }
    //Creates the new matrix
    Matrix result(_rows, _cols);
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols; j++){
            result(i,j) = ((*this)(i,j) + mat_1(i,j));
        }
    }
    return result;
}

//assignment operator
Matrix & Matrix::operator=(const Matrix&mat_1){
    if (this == &mat_1){
        return *this;
    }
    //    update_mat(mat_1.get_rows(),
    //    mat_1.get_cols());
    //    for(int i = 0; i < _rows; i++){
    //        for(int j = 0; j < _cols; j++){
    //            _mat[i][j] = mat_1(i,j);
    //        }
    //    }
    float* curr = new float[mat_1.get_cols()*mat_1.get_rows()];
    delete[] _mat;
    _rows = mat_1.get_rows();
    _cols = mat_1.get_cols();
    _mat = curr;
    for(int j = 0; j < _rows * _cols; j++)
    {
        _mat[j] = mat_1._mat[j];
    }
    return *this;
}

//matrix multiplication operator
Matrix Matrix::operator*(const Matrix& mat_1)const{
    if(_cols != mat_1.get_rows()){
        std::cerr << "Error: Matrices of"
                     " these sizes can not"
                     " be multiplied." << std::endl;
        exit(EXIT_FAILURE);
    }
    //Creates the new matrix
    Matrix result(_rows, mat_1.get_cols());
    float count;
    for(int k = 0; k < _rows; k++){
        for(int i = 0; i < mat_1.get_cols(); i++){
            count = 0;
            for(int j = 0; j < _cols; j++){
                count += ((*this)(k,j) * mat_1(j,i));
            }
            result(k,i) = count;
        }
    }
    return result;
}

//scalar multiplication operator on the right
Matrix Matrix::operator*(float c)const{
    Matrix result(_rows, _cols);
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols; j++){
            result(i,j) = (*this)(i,j) * c;
        }
    }
    return result;
}

//scalar multiplication operator on the left
Matrix operator*(float c, const Matrix& rhs){
    return rhs * c;
}

//matrix addition accumulation operator
Matrix & Matrix::operator+=(const Matrix & mat_1){
    if(mat_1.get_cols() != _cols
    || mat_1.get_rows() != _rows){
        std::cerr << "Error: Matrices"
                     " of different sizes"
                     " can not be added." << std::endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < _rows; i++){
        for(int j = 0; j < _cols; j++){
            (*this)(i,j) += mat_1(i,j);
        }
    }
    return *this;
}

//() const operator
float Matrix::operator()(int const ind_i,
        int const ind_j) const{
    return _mat[ind_j + (ind_i * _cols)];
}

//() operator
float& Matrix::operator()(int const ind_i,
        int const ind_j){
    return _mat[ind_j + (ind_i * _cols)];
}

//[] const operator
float Matrix::operator[](int const ind) const{
//    int row = (int) ind / _cols;
//    int col = (int) ind % _cols;
//    return _mat[row][col];
return _mat[ind];
}

//[] operator
float& Matrix::operator[](int const ind){
//    int row = (int) ind / _cols;
//    int col = (int) ind % _cols;
//    return _mat[row][col];
return _mat[ind];
}

//<< operator
std::ostream& operator<<(std::ostream& s,
        const Matrix& mat_1){
    for(int i = 0; i < mat_1.get_rows(); i++){
        for(int j = 0;
        j < mat_1.get_cols(); j++){
            if(mat_1(i,j) >= PRINT_NUM){
                //double space
                s << "  ";
            }
            else{
                //double asterisk
                s << "**";
            }
        }
        s << std::endl;
    }
    return s;
}