#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <new>

#define throw(...)

class Matrix
{
    typedef unsigned int uint;

public:
    Matrix();
    Matrix(const uint size);
    Matrix(const uint height, const uint width);
    ~Matrix();

    double getWidth() const;
    double getHeight() const;

    void resize(uint newSize) throw(std::bad_alloc);
    void resize(uint newWidth, uint newHeight) throw(std::bad_alloc);

    Matrix operator+(const Matrix &other) const throw(std::bad_alloc, std::invalid_argument);
    Matrix operator-(const Matrix &other) const throw(std::bad_alloc, std::invalid_argument);
    Matrix operator*(const Matrix &other) const throw(std::bad_alloc, std::invalid_argument);
    Matrix operator*(const double other) const throw(std::bad_alloc);

    double *operator[](unsigned int rowIndex) throw(std::range_error);
    const double *operator[](unsigned int rowIndex) const throw(std::range_error);

private:
    double **m_data = nullptr;
    unsigned int m_width;
    unsigned int m_height;

    void allocData() throw(std::bad_alloc);
    void deallocData();
};

#endif // MATRIX_H
