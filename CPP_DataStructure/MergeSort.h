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

void Test()
{
    int dataSet[] = {334, 6, 4, 2, 3, 1, 5, 117, 12, 34};
    int length = sizeof dataSet / sizeof dataSet[0];
    int i = 0;

    MergeSort(dataSet, 0, length - 1);
    for (i = 0; i < length; ++i)
        cout << dataSet[i] << " ";

    cout << endl;
}