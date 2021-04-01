#include "matrix.h"

Matrix::Matrix(): Matrix(1)
{
}

Matrix::Matrix(const unsigned int size): Matrix(size, size) {  }

Matrix::Matrix(const unsigned int height, const unsigned int width):
    m_width(width), m_height(height)
{
    allocData();
}

Matrix::~Matrix()
{
    deallocData();
}

double Matrix::getWidth() const
{
    return m_width;
}

double Matrix::getHeight() const
{
    return m_height;
}

std::tuple<double, int, int> Matrix::findMax() const
{
    double max = __DBL_MIN__;
    int maxI, maxJ;
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            if (m_data[i][j] > max) {
                max = m_data[i][j];
                maxI = i;
                maxJ = j;
            }
        }
    }
    return std::make_tuple(max, maxI, maxJ);
}

double Matrix::findMaxInColumn(int column) const
{
    double max = __DBL_MIN__;
    for (unsigned int row = 0; row < m_height; ++row) {
        if (m_data[row][column] > max) {
            max = m_data[row][column];
        }
    }
    return max;
}

double Matrix::findMin() const
{
    double min = __DBL_MAX__;
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            if (m_data[i][j] < min) {
                min = m_data[i][j];
            }
        }
    }
    return min;
}

double Matrix::findMinInRow(int row) const
{
    double min = __DBL_MIN__;
    for (unsigned int column = 0; column < m_height; ++column) {
        if (m_data[row][column] > min) {
            min = m_data[row][column];
        }
    }
    return min;
}

void Matrix::resize(int newSize)
{
    resize(newSize, newSize);
}

void Matrix::resize(int newWidth, int newHeight)
{
    deallocData();

    m_width = newWidth;
    m_height = newHeight;

    allocData();
}

Matrix Matrix::operator+(const Matrix &other) const
{
    if (m_width != other.m_width || m_height != other.m_height)
        throw std::invalid_argument("Can't add matricies with different sizes!");

    Matrix result(m_height, m_width);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            result.m_data[i][j] = this->m_data[i][j] + other.m_data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const
{
    if (m_width != other.m_width || m_height != other.m_height)
        throw std::invalid_argument("Can't substract matricies with different sizes!");
    Matrix result(m_height, m_width);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            result.m_data[i][j] = this->m_data[i][j] - other.m_data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const double scalar) const
{
    Matrix result(m_height, m_width);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            result.m_data[i][j] = this->m_data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const
{
    if (m_width != other.m_height)
        throw std::invalid_argument("Matricies have incompatible sizes!");

    Matrix result(m_height, other.m_width);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < other.m_width; ++j) {
            for (unsigned int k = 0; k < m_width; ++k) {
                result.m_data[i][j] += this->m_data[i][k] * other.m_data[k][j];
            }
        }
    }
    return result;
}

double *Matrix::operator[](unsigned int rowIndex)
{
    return m_data[rowIndex];
}

const double *Matrix::operator[](unsigned int rowIndex) const
{
    return m_data[rowIndex];
}

void Matrix::allocData()
{
    m_data = new double*[m_height];
    for (unsigned int i = 0; i < m_height; ++i) {
        m_data[i] = new double[m_width]();
    }
}

void Matrix::deallocData()
{
    if (m_data == nullptr)
        return;

    for (unsigned int i = 0; i < m_height; ++i) {
        if (m_data[i] != nullptr)
            delete[] m_data[i];
    }
    delete[] m_data;
}
