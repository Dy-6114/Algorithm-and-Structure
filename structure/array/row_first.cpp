#include <iostream>
#include <cstdarg>

using namespace std;

const int OK = 1;
const int ERROR = -1;
const int MAX_DIM = 8;

typedef int ElemType;

typedef struct
{
    ElemType *base;
    int dim;
    int *constants; // 数组映像函数常量基址
    int *bounds;    // 数组维界基址
} Array;

int initArray(Array *, int dim, ...);             // 初始化
void destroyArray(Array *);                       // 销毁
int locate(const Array *pArr, int nDim, va_list); // 定位下标指向的元素在数组中的位置
int assign(Array *pArr, ElemType *elm, ...);      // 数组赋值
int value(const Array *pArr, ElemType *elm, ...); // 数组取值

// 测试
int main()
{
    Array arr;

    /// 初始化一个三维数组, 大小为 2x3x5
    initArray(&arr, 3, 2, 3, 5);

    int a = 0;
    /// 赋值测试
    int i = 0, m = 0, n = 0;
    for (i = 0; i < 2; ++i)
        for (m = 0; m < 3; ++m)
            for (n = 0; n < 5; ++n)
            {
                a = i + m + n;
                assign(&arr, &a, i, m, n);
            }
    int b = 0;
    /// 取值测试
    for (i = 0; i < 2; ++i)
        for (m = 0; m < 3; ++m)
            for (n = 0; n < 5; ++n)
            {
                value(&arr, &b, i, m, n);
                cout << "[" << i << "][" << m << "][" << n << "]=" << b << endl;
            }
    /// 销毁数组
    destroyArray(&arr);

    return 0;
}

int initArray(Array *arr, int ndim, ...)
{
    if (ndim < 1 || ndim > MAX_DIM)
        return ERROR;
    arr->dim = ndim;
    arr->bounds = new int[ndim];
    if (!arr->bounds)
        return ERROR;
    int i = 0, nElemCount = 1;
    va_list ap;
    va_start(ap, ndim);
    for (i = 0; i < ndim; i++)
    {
        arr->bounds[i] = va_arg(ap, int);
        if (arr->bounds[i] < 0)
            return ERROR;
        nElemCount *= arr->bounds[i];
    }
    va_end(ap);

    arr->base = new ElemType[nElemCount];
    if (!arr->base)
        return ERROR;

    arr->constants = new int[ndim];
    arr->constants[ndim - 1] = 1;
    for (i = ndim - 2; i >= 0; i--)
    {
        arr->constants[i] = arr->constants[i + 1] * arr->bounds[i + 1];
    }

    return OK;
}

void destroyArray(Array *arr)
{
    if (arr->base)
        delete[] arr->base;
    if (arr->bounds)
        delete[] arr->bounds;
    if (arr->constants)
        delete[] arr->constants;
}

int locate(const Array *arr, int ndim, va_list ap)
{
    int pos = 0, ind = 0;
    for (int i = 0; i < ndim; i++)
    {
        ind = va_arg(ap, int);
        if (ind >= 0 && ind < arr->bounds[i])
            pos += arr->constants[i] * ind;
        else
            return ERROR;
    }
    va_end(ap);
    return pos;
}

int assign(Array *arr, ElemType *elem, ...)
{
    int pos = 0;
    va_list ap;
    va_start(ap, elem);
    pos = locate(arr, arr->dim, ap);
    if (pos == ERROR)
    {
        cout << "pos error";
        return ERROR;
    }
    arr->base[pos] = *elem;

    return OK;
}

int value(const Array *arr, ElemType *elem, ...)
{
    int pos = 0;
    va_list ap;
    va_start(ap, elem);
    pos = locate(arr, arr->dim, ap);
    *elem = arr->base[pos];

    return OK;
}