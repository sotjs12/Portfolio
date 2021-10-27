#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N;
const int MOD = 10 * 1000 * 1000;
const int MAX = 100;
int dp[MAX + 1][MAX + 1];

//N 개의 이전에 0개의 정사각형이 존재 정사각형으로 된 폴리오미노 개수
int solve(int n, int f)
{
  if (n == f)
    return 1;
  int &ret = dp[n][f];
  if (ret != -1)
    return ret;
  ret = 0;
  for (int s = 1; s <= n - f; ++s)
  {
    int add = (f + s - 1);
    add *= solve(n - f, s);
    add %= MOD;
    ret += add;
    ret %= MOD;
  }

  return ret;
}

int main()
{
  freopen("POLY.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    cin >> N;

    int result = 0;
    for (int i = 1; i <= N; ++i)
      result = (result + solve(N, i)) % MOD;

    cout << result << endl;
  }

  return 0;
}