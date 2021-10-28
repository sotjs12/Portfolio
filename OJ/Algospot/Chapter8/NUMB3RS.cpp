#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N, D, P, T, TARGET;
const int MAX = 50;
const int MAX_DAY = 100;
double dp[MAX + 1][MAX_DAY + 1];
int arr[MAX + 1][MAX + 1];
int deg[MAX + 1];

// 탈옥 후 d 일 이후에 h 에 있을 확률
double solve(int h, int d)
{
  if (d == 0)
    return (h == TARGET ? 1.0 : 0.0);
  double &ret = dp[h][d];
  if (ret != -1.0)
    return ret;
  ret = 0.0;
  for (int t = 0; t < N; ++t)
    if (arr[h][t] == 1)
      ret += solve(t, d - 1) / deg[h];

  return ret;
}

int main()
{
  freopen("NUMB3RS.txt", "r", stdin);
  cin >> C;
  while (C--)
  {

    memset(arr, -1, sizeof(arr));
    memset(deg, 0, sizeof(deg));

    cin >> N >> D >> P;
    for (int y = 0; y < N; ++y)
      for (int x = 0; x < N; ++x)
      {
        cin >> arr[y][x];
        deg[y] += arr[y][x];
      }
    cin >> T;
    for (int i = 0; i < T; ++i)
    {
      for (int y = 0; y <= MAX; ++y)
        for (int x = 0; x <= MAX_DAY; ++x)
          dp[y][x] = -1.0;

      cin >> TARGET;
      cout.precision(11);
      cout << solve(P, D) << " ";
    }
    cout << endl;
  }

  return 0;
}