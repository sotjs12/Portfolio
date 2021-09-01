#include <iostream>

using namespace std;

void PrintSolution(int columns[], int numberOfQueens);
int IsThreatened(int columns[], int newRow);
void FindSolutionForQueen(int columns[], int row, int numberOfQueens, int *solutionCount);

void PrintSolution(int columns[], int numberOfQueens)
{
    int i = 0, j = 0;
    for (i = 0; i < numberOfQueens; ++i)
    {
        for (j = 0; j < numberOfQueens; ++j)
        {
            if (columns[i] == j)
                cout << "Q";
            else
                cout << ".";
        }
        cout << endl;
    }
    cout << endl;
}
int IsThreatened(int columns[], int newRow)
{
    int current = 0;
    int failed = 0;
    while (current < newRow)
    {
        if (columns[current] == columns[newRow])
        {
            failed = 1;
            break;
        }
        else if (abs(columns[current] - columns[newRow]) == abs(current - newRow))
        {
            failed = 1;
            break;
        }
        current++;
    }

    return failed;
}
void FindSolutionForQueen(int columns[], int row, int numberOfQueens, int *solutionCount)
{
    if (IsThreatened(columns, row))
        return;

    if (row == numberOfQueens - 1)
    {
        (*solutionCount)++;
        PrintSolution(columns, numberOfQueens);
        return;
    }

    for (int i = 0; i < numberOfQueens; ++i)
    {
        columns[row + 1] = i;
        FindSolutionForQueen(columns, row + 1, numberOfQueens, solutionCount);
    }
}

void Test()
{
    int numberOfQueens = 8;
    int solutionCount = 0;
    int *columns = (int *)malloc(sizeof(int) * numberOfQueens);

    for (int i = 0; i < numberOfQueens; ++i)
    {
        columns[0] = i;
        FindSolutionForQueen(columns, 0, numberOfQueens, &solutionCount);
    }
    free(columns);
}