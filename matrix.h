#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <tuple>

class Matrix
{
public:
    Matrix();
    Matrix(const unsigned int size);
    Matrix(const unsigned int height, const unsigned int width);
    ~Matrix();

    double getWidth() const;
    double getHeight() const;

    std::tuple<double, int, int> findMax() const;
    double findMaxInColumn(int columnIndex) const;

    double findMin() const;
    double findMinInRow(int rowIndex) const;

    void resize(int newSize);
    void resize(int newWidth, int newHeight);

    Matrix operator+(const Matrix &other) const;
    Matrix operator-(const Matrix &other) const;
    Matrix operator*(const Matrix &other) const;
    Matrix operator*(const double other) const;

    double *operator[](unsigned int rowIndex);
    const double *operator[](unsigned int rowIndex) const;

private:
    double **m_data = nullptr;
    unsigned int m_width;
    unsigned int m_height;

    void allocData();
    void deallocData();
};

#endif // MATRIX_H
