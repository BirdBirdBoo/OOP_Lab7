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

void Matrix::resize(uint newSize) throw(std::bad_alloc)
{
    resize(newSize, newSize);
}

void Matrix::resize(uint newWidth, uint newHeight) throw(std::bad_alloc)
{
    deallocData();

    m_width = newWidth;
    m_height = newHeight;

    allocData();
}

Matrix Matrix::operator+(const Matrix &other) const throw(std::bad_alloc, std::invalid_argument)
{
    if (m_width != other.m_width || m_height != other.m_height)
        throw std::invalid_argument("Can't add matrices with different sizes!");

    Matrix result(m_height, m_width);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            result.m_data[i][j] = this->m_data[i][j] + other.m_data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator-(const Matrix &other) const throw(std::bad_alloc, std::invalid_argument)
{
    if (m_width != other.m_width || m_height != other.m_height)
        throw std::invalid_argument("Can't substract matrices with different sizes!");
    Matrix result(m_height, m_width);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            result.m_data[i][j] = this->m_data[i][j] - other.m_data[i][j];
        }
    }
    return result;
}

Matrix Matrix::operator*(const double scalar) const throw(std::bad_alloc)
{
    Matrix result(m_height, m_width);
    for (unsigned int i = 0; i < m_height; ++i) {
        for (unsigned int j = 0; j < m_width; ++j) {
            result.m_data[i][j] = this->m_data[i][j] * scalar;
        }
    }
    return result;
}

Matrix Matrix::operator*(const Matrix &other) const throw(std::bad_alloc, std::invalid_argument)
{
    if (m_width != other.m_height)
        throw std::invalid_argument("Matrices have incompatible sizes!");

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

double *Matrix::operator[](unsigned int rowIndex) throw(std::range_error)
{
    return m_data[rowIndex];
}

const double *Matrix::operator[](unsigned int rowIndex) const throw(std::range_error)
{
    return m_data[rowIndex];
}

void Matrix::allocData() throw(std::bad_alloc)
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
