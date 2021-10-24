#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, LEN;
string str;
const int MAX = 10000;
const int INF = 987654321;
int dp[MAX + 1];

int classify(int from, int to)
{
  bool result = true;
  for (int i = from + 1; i <= to; ++i)
  {
    if (str[from] != str[i])
    {
      result = false;
      break;
    }
  }
  if (result)
    return 1;

  result = true;
  for (int i = from, diff = (str[from] < str[from + 1] ? -1 : 1); i < to; ++i)
  {
    if ((str[i] - str[i + 1]) != diff)
    {
      result = false;
      break;
    }
  }
  if (result)
    return 2;

  result = true;
  for (int i = from, diff = (str[from] - str[from + 1]); i < to; ++i, diff *= -1)
  {
    if (str[i] - str[i + 1] != diff)
    {
      result = false;
      break;
    }
  }
  if (result)
    return 4;

  result = true;
  for (int i = from, diff = (str[from] - str[from + 1]); i < to; ++i)
  {
    if (str[i] - str[i + 1] != diff)
    {
      result = false;
      break;
    }
  }
  if (result)
    return 5;

  return 10;
}

//idx 부터의 최소값
int solve(int idx)
{
  if (LEN == idx)
    return 0;
  int &ret = dp[idx];
  if (ret != -1)
    return ret;

  ret = INF;
  for (int i = 3; i <= 5; ++i)
    if (idx + i <= LEN)
      ret = min(ret, classify(idx, idx + i - 1) + solve(idx + i));

  return ret;
}

int main()
{
  freopen("PI.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));

    cin >> str;
    LEN = str.length();
    cout << solve(0) << endl;
  }

  return 0;
}