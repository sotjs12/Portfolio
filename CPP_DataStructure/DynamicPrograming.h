#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

typedef unsigned long ULONG;

ULONG Fibonacci(int n)
{
    if (n == 0 || n == 1)
        return n;

    ULONG *dp = (ULONG *)malloc(sizeof(ULONG) * (n + 1));
    dp[0] = 0;
    dp[1] = 1;
    for (int i = 2; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];

    ULONG ret = dp[n];
    free(dp);
    return ret;
}

void Fibonacci_Test()
{
    int N = 46;
    ULONG result = Fibonacci(N);
    // cout << result << endl;
}

typedef struct structLCSTable
{
    int **data;
} LCSTable;

int LCS(char *X, char *Y, int i, int j, LCSTable *dp)
{
    int m = 0, n = 0;

    for (m = 0; m <= i; ++m)
        dp->data[m][0] = 0;
    for (n = 0; n <= j; ++n)
        dp->data[0][n] = 0;

    for (m = 1; m <= i; ++m)
    {
        for (n = 1; n <= j; ++n)
        {
            if (X[m - 1] == Y[n - 1])
            {
                dp->data[m][n] = dp->data[m - 1][n - 1] + 1;
            }
            else
            {
                if (dp->data[m][n - 1] >= dp->data[m - 1][n])
                {
                    dp->data[m][n] = dp->data[m][n - 1];
                }
                else
                {
                    dp->data[m][n] = dp->data[m - 1][n];
                }
            }
        }
    }

    return dp->data[i][j];
}
void LCS_Trackback(char *X, char *Y, int m, int n, LCSTable *dp, char *result)
{
    if (m == 0 || n == 0)
        return;

    int current = dp->data[m][n];
    int left = dp->data[m][n - 1];
    int leftUp = dp->data[m - 1][n - 1];
    int up = dp->data[m - 1][n];

    if (current > left && current > leftUp && current > up)
    {
        char tmpLCS[100];
        strcpy(tmpLCS, result);
        sprintf(result, "%c%s", X[m - 1], tmpLCS);

        LCS_Trackback(X, Y, m - 1, n - 1, dp, result);
    }
    else if (current > up && current == left)
    {
        LCS_Trackback(X, Y, m, n - 1, dp, result);
    }
    else
    {
        LCS_Trackback(X, Y, m - 1, n, dp, result);
    }
}
void LCS_Test()
{
    char *X = "GOOD MORNING.";
    char *Y = "GUTEN MORGEN.";
    char *result;

    int len_x = strlen(X);
    int len_y = strlen(Y);

    int i = 0;
    int j = 0;
    int length = 0;

    LCSTable dp;
    dp.data = (int **)malloc(sizeof(int) * (len_x + 1));
    for (i = 0; i < len_x; ++i)
    {
        dp.data[i] = (int *)malloc(sizeof(int) * (len_y + 1));
        memset(dp.data[i], 0, sizeof(int) * (len_y + 1));
    }
    length = LCS(X, Y, len_x, len_y, &dp);

    result = (char *)malloc(sizeof(dp.data[len_x][len_y] + 1));
    LCS_Trackback(X, Y, len_x, len_y, &dp, result);
    printf("%s", result);
}

void Test()
{
    LCS_Test();
}