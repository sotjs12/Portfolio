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

//n 개의 타일을 세는 방법
int solve(int n)
{
  if (n <= 1)
    return 1;

  int &ret = dp[n];
  if (ret != -1)
    return ret;
  return ret = (solve(n - 1) + solve(n - 2)) % MOD;
}

int main()
{
  freopen("TILING2.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    cin >> N;
    cout << solve(N) << endl;
  }

  return 0;
}