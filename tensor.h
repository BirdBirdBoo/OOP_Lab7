#ifndef TENSOR_H
#define TENSOR_H

#include <stdexcept>

class Tensor
{

public:
    Tensor(const int dimensionCount, const int *dimensions);
    ~Tensor();

    Tensor operator[](int index);
    operator double();
    double operator=(double a);

private:
    Tensor(double* dataPtr, const int dimensionCount, const int *dimensions);

    double *mData = nullptr;
    int mDimensionCount;
    int *mDimensions;

    void copyDimensions(const int* dims);

    bool isSubTensor;

    void allocData();
    void deallocData();
};

#endif // TENSOR_H
