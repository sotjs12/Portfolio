#include <iostream>

using namespace std;

void MergeSort(int dataSet[], int sIndex, int eIndex);
void Merge(int dataSet[], int sIndex, int mIndex, int eIndex);

void MergeSort(int dataSet[], int sIndex, int eIndex)
{
    if (eIndex - sIndex < 1)
        return;
    int mIndex = (sIndex + eIndex) / 2;
    MergeSort(dataSet, sIndex, mIndex);
    MergeSort(dataSet, mIndex + 1, eIndex);
    Merge(dataSet, sIndex, mIndex, eIndex);
}
void Merge(int dataSet[], int sIndex, int mIndex, int eIndex)
{
    int left = sIndex;
    int right = mIndex + 1;

    int *array = (int *)malloc(sizeof(dataSet[0]) * (eIndex - sIndex + 1));
    int idx = 0;

    while (left <= mIndex && right <= eIndex)
        array[idx++] = (dataSet[left] > dataSet[right])
                           ? dataSet[right++]
                           : dataSet[left++];

    while (left <= mIndex)
        array[idx++] = dataSet[left++];
    while (right <= eIndex)
        array[idx++] = dataSet[right++];

    for (int i = sIndex, idx = 0; i <= eIndex; ++i, ++idx)
        dataSet[i] = array[idx];

    free(array);
}

void Test_MergeSort()
{
    int dataSet[] = {334, 6, 4, 2, 3, 1, 5, 117, 12, 34};
    int length = sizeof dataSet / sizeof dataSet[0];
    int i = 0;

    MergeSort(dataSet, 0, length - 1);
    for (i = 0; i < length; ++i)
        cout << dataSet[i] << " ";

    cout << endl;
}

typedef unsigned long ULONG;

ULONG Power(int base, int exponent)
{
    if (exponent == 1)
        return base;
    else if (exponent == 0)
        return 1;

    ULONG ret;
    if (exponent % 2 == 0)
    {
        ret = Power(base, exponent / 2);
        return ret * ret;
    }
    else
    {
        ret = Power(base, (exponent - 1) / 2);
        return ret * ret * base;
    }
}

typedef struct tagMatrix2x2
{
    ULONG data[2][2];
} Matrix2x2;

ULONG Finobacci(int n);
Matrix2x2 Matrix2x2_Multiply(Matrix2x2 A, Matrix2x2 B);
Matrix2x2 Matrix2x2_Power(Matrix2x2 A, int n);

ULONG Finobacci(int n)
{
    Matrix2x2 A;
    A.data[0][0] = 1;
    A.data[0][1] = 1;
    A.data[1][0] = 1;
    A.data[1][1] = 0;

    A = Matrix2x2_Power(A, n);

    return A.data[0][1];
}

Matrix2x2 Matrix2x2_Multiply(Matrix2x2 A, Matrix2x2 B)
{
    Matrix2x2 C;
    C.data[0][0] = A.data[0][0] * B.data[0][0] + A.data[0][1] * B.data[1][0];
    C.data[0][1] = A.data[0][0] * B.data[1][0] + A.data[0][1] * B.data[1][1];

    C.data[1][0] = A.data[1][0] * B.data[0][0] + A.data[1][1] * B.data[1][0];
    C.data[1][1] = A.data[1][0] * B.data[1][0] + A.data[1][1] * B.data[1][1];

    return C;
}

Matrix2x2 Matrix2x2_Power(Matrix2x2 A, int n)
{
    if (n > 1)
    {
        A = Matrix2x2_Power(A, n / 2);
        A = Matrix2x2_Multiply(A, A);
        if (n & 1)
        {
            Matrix2x2 B;
            B.data[0][0] = 1;
            B.data[0][1] = 1;
            B.data[1][0] = 1;
            B.data[1][1] = 0;
            A = Matrix2x2_Multiply(A, B);
        }
    }

    return A;
}

void Test_Fibonacci()
{
    int N = 46;
    ULONG result = Finobacci(N);
    cout << result << endl;
}

void Test()
{
    Test_Fibonacci();
}