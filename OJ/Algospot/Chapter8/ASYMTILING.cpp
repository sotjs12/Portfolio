#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N;
const int MAX = 100;
const int MOD = 1000000007;
int dp[MAX + 1];

int tiling(int n)
{
  if (n <= 1)
    return 1;
  int &ret = dp[n];
  if (ret != -1)
    return ret;

  return ret = (tiling(n - 1) + tiling(n - 2)) % MOD;
}
//n 번째 줄까지 타일을 체우는 가지수
int solve(int n)
{
  int ret = tiling(n);
  if (n % 2 == 0)
  {
    ret = (ret - tiling(n / 2) + MOD) % MOD;
    ret = (ret - tiling(n / 2 - 1) + MOD) % MOD;
  }
  else
  {
    ret = (ret - tiling(n / 2) + MOD) % MOD;
  }
  return ret;
}

int main()
{
  freopen("ASYMTILING.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    cin >> N;
    cout << solve(N) << endl;
  }

  return 0;
}