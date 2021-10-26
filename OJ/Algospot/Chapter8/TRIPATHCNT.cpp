#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N;
const int MAX = 100;
int dp[MAX + 1][MAX + 1];
int dp2[MAX + 1][MAX + 1];
int arr[MAX + 1][MAX + 1];

int maxPath(int y, int x)
{
  if (y == N - 1)
    return arr[y][x];
  int &ret = dp2[y][x];
  if (ret != -1)
    return ret;

  return ret = arr[y][x] + max(maxPath(y + 1, x), maxPath(y + 1, x + 1));
}

//y,x 에서 시작하는 최대합 경로의 수
int solve(int y, int x)
{
  if (y == N - 1)
    return 1;

  int &ret = dp[y][x];
  if (ret != -1)
    return ret;

  int pathA = maxPath(y + 1, x);
  int pathB = maxPath(y + 1, x + 1);

  if (pathA > pathB)
    ret = solve(y + 1, x);
  else if (pathA < pathB)
    ret = solve(y + 1, x + 1);
  else
    ret = solve(y + 1, x) + solve(y + 1, x + 1);

  return ret;
}

int main()
{
  freopen("TRIPATHCNT.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    memset(dp2, -1, sizeof(dp2));
    memset(arr, -1, sizeof(arr));

    cin >> N;
    for (int y = 0; y < N; ++y)
      for (int x = 0; x <= y; ++x)
        cin >> arr[y][x];

    cout << solve(0, 0) << endl;
  }

  return 0;
}
