#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N, P, L;
const int MAX = 50;
const int MAX_C = 1000000000 + 1;
int dp[MAX + 1];
const string EXPAND_X = "X+YF";
const string EXPAND_Y = "FX-Y";

// g세대에 스킵해야할 문자열 수 계산
void preCalc()
{
  dp[0] = 1;
  for (int i = 1; i <= 50; ++i)
    dp[i] = min(MAX_C, dp[i - 1] * 2 + 2);
}

// g 세대에서 skip 번째 드래곤커브 문자
char solve(const string &result, int g, int skip)
{
  if (g == 0)
  {
    if (skip > result.size())
      exit(-1);
    return result[skip];
  }
  for (int i = 0; i < result.size(); ++i)
    if (result[i] == 'X' || result[i] == 'Y')
      if (skip >= dp[g])
        skip -= dp[g];
      else if (result[i] == 'X')
        return solve(EXPAND_X, g - 1, skip);
      else
        return solve(EXPAND_Y, g - 1, skip);
    else if (skip > 0)
      --skip;
    else
      return result[i];

  return '#';
}

int main()
{
  freopen("DRAGON.txt", "r", stdin);
  preCalc();
  cin >> C;
  while (C--)
  {
    cin >> N >> P >> L;
    for (int i = 0; i < L; ++i)
      cout << solve("FX", N, P + i - 1);
    cout << endl;
  }

  return 0;
}