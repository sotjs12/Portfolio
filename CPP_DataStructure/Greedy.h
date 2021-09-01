#include <iostream>

using namespace std;

int Compare(const void *a, const void *b)
{
    int _a = *(int *)a;
    int _b = *(int *)b;
    if (_a < _b)
        return 1;
    else
        return -1;
}
void GetChange(int price, int pay, int coinUnits[], int change[], int size);
int CountConins(int amount, int coinUnit);
void PrintChange(int coinUnits[], int change[], int size);

void GetChange(int price, int pay, int coinUnits[], int change[], int size)
{
    int amount = pay - price;
    for (int i = 0; i < size && amount > 0; ++i)
    {
        change[i] = CountConins(amount, coinUnits[i]);
        amount -= change[i] * coinUnits[i];
    }
}
void GetChange_DP(int price, int pay, int coinUnits[], int change[], int size)
{
    int amount = pay - price;
    int *dp = (int *)malloc(sizeof(int) * (amount + 1));
    int *dp_coin = (int *)malloc(sizeof(int) * (amount + 1));
    memset(dp, 0, sizeof(int) * (amount + 1));
    memset(dp_coin, -1, sizeof(int) * (amount + 1));

    for (int i = 1, minValue, j; i <= amount; ++i)
    {
        minValue = 9999;
        j = size - 1;
        while (j >= 0 && coinUnits[j] <= i)
        {
            if (minValue > dp[i - coinUnits[j]])
            {
                dp_coin[i] = j;
                minValue = dp[i - coinUnits[j]];
            }
            j--;
        }

        dp[i] = minValue + 1;
    }

    int _amount = amount;
    while (_amount > 0)
    {
        if (dp_coin[_amount] < 0)
            break; // 해가 없음
        change[dp_coin[_amount]]++;
        _amount -= coinUnits[dp_coin[_amount]];
    }
}
int CountConins(int amount, int coinUnit)
{
    int count = 0;
    while (amount >= coinUnit)
    {
        amount -= coinUnit;
        count++;
    }
    return count;
}
void PrintChange(int coinUnits[], int change[], int size)
{
    for (int i = 0; i < size; ++i)
        cout << coinUnits[i] << "원 : " << change[i] << "개" << endl;
}

void Test_Change()
{
    int unitCount = 5;
    int price = 1200;
    int pay = 2000;
    int *coinUnits = (int *)malloc(sizeof(int) * unitCount);
    int *change = (int *)malloc(sizeof(int) * unitCount);

    coinUnits[0] = 500;
    coinUnits[1] = 100;
    coinUnits[2] = 50;
    coinUnits[3] = 10;
    coinUnits[4] = 1;

    GetChange(price, pay, coinUnits, change, unitCount);
    PrintChange(coinUnits, change, unitCount);
}
void Test_Change_DP()
{
    int unitCount = 5;
    int price = 1200;
    int pay = 2000;
    int *coinUnits = (int *)malloc(sizeof(int) * unitCount);
    int *change = (int *)malloc(sizeof(int) * unitCount);

    coinUnits[0] = 500;
    coinUnits[1] = 400;
    coinUnits[2] = 50;
    coinUnits[3] = 10;
    coinUnits[4] = 1;

    GetChange_DP(price, pay, coinUnits, change, unitCount);
    PrintChange(coinUnits, change, unitCount);
}

void Test()
{
    Test_Change_DP();
}