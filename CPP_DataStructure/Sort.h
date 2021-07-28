#include <iostream>
#include <stack>

using namespace std;

void Swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void BubbleSort(int dataSet[], int len)
{
    int i = 0, j = 0, temp = 0;
    for (i = 0; i < len; ++i)
    {
        bool swaped = false;
        for (j = 0; j < len - i - 1; ++j)
        {
            if (dataSet[j] > dataSet[j + 1])
            {
                Swap(&dataSet[j], &dataSet[j + 1]);
                swaped = true;
            }
        }
        if (!swaped)
        {
            break;
        }
    }
}

void BubbleSortTest()
{
    int dataSet[] = {6, 4, 2, 3, 1, 5};
    int length = sizeof dataSet / sizeof dataSet[0];
    int i = 0;
    BubbleSort(dataSet, length);
    for (i = 0; i < length; ++i)
    {
        cout << dataSet[i] << ",";
    }
    cout << endl;
}

void InsertionSort(int dataSet[], int len)
{
    int i, j, value;

    for (i = 1; i < len; ++i)
    {
        if (dataSet[i - 1] <= dataSet[i])
            continue;

        value = dataSet[i];
        for (j = 0; j < i; ++j)
        {
            if (value < dataSet[j])
            {
                memmove(&dataSet[j + 1], &dataSet[j], sizeof(dataSet[0]) * (i - j));
                dataSet[j] = value;
                break;
            }
        }
    }
}

void InsertionSortTest()
{
    int dataSet[] = {6, 4, 2, 3, 1, 5};
    int length = sizeof dataSet / sizeof dataSet[0];
    int i = 0;
    InsertionSort(dataSet, length);
    for (i = 0; i < length; ++i)
    {
        cout << dataSet[i] << ",";
    }
    cout << endl;
}

int Partition(int dataSet[], int left, int right)
{
    int pivot = left;
    int pivotData = dataSet[pivot];
    right += 1;
    while (left < right)
    {
        while (dataSet[++left] < pivotData)
            ;
        while (dataSet[--right] > pivotData)
            ;
        if (left < right)
        {
            Swap(&dataSet[left], &dataSet[right]);
        }
    }

    Swap(&dataSet[pivot], &dataSet[right]);
    return right;
}

void QuickSort(int dataSet[], int left, int right)
{
    if (left < right)
    {
        int partition = Partition(dataSet, left, right);
        QuickSort(dataSet, left, partition - 1);
        QuickSort(dataSet, partition + 1, right);
    }
}
void QuickSortStack(int dataSet[], int left, int right)
{
    stack<int> s;
    do
    {
        while (left < right)
        {
            int pivot = Partition(dataSet, left, right);
            if (pivot - left < right - pivot)
            {
                s.push(pivot + 1);
                s.push(right);
                right = pivot - 1;
            }
            else
            {
                s.push(left);
                s.push(pivot - 1);
                left = pivot + 1;
            }
        }
        if (s.empty())
            break;

        right = s.top();
        s.pop();
        left = s.top();
        s.pop();

    } while (true);
}

void QuickSortTest()
{
    int dataSet[] = {6, 4, 2, 3, 1, 5, 10, 23, 6, 5, 22};
    int length = sizeof dataSet / sizeof dataSet[0];
    int i = 0;
    QuickSortStack(dataSet, 0, length - 1);
    for (i = 0; i < length; ++i)
    {
        cout << dataSet[i] << ",";
    }
    cout << endl;
}

void Test()
{
    QuickSortTest();
}