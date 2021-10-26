#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N, M;
const int MAX = 1000;
double dp[MAX + 1][MAX * 2 + 1];

double solve(int n, int m)
{
  if (m == M)
    return (n >= N) ? 1 : 0;

  double &ret = dp[n][m];
  if (ret != -1.0)
    return ret;

  return ret = (solve(n + 2, m + 1) * 0.75) + (solve(n + 1, m + 1) * 0.25);
}

int main()
{
  freopen("SNAIL.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    for (int i = 0; i < 1000; i++)
      for (int j = 0; j < MAX * 2 + 1; j++)
        dp[i][j] = -1.0;

    cin >> N >> M;
    cout.precision(10);
    cout << fixed << solve(0, 0) << '\n';
  }

  return 0;
}