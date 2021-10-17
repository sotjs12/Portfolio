#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int C, N, IN;
const int MAX = 500;
int dp[MAX + 1];
int seq[MAX + 1];

// Sub quest : x에서부터 시작하는 최대 증가 순열 길이 반환
int solve(int x)
{
  int &ret = dp[x + 1];
  if (ret != -1)
    return ret;
  ret = 1;
  for (int i = x + 1; i < N; ++i)
    if (x == -1 || seq[x] < seq[i])
      ret = max(ret, solve(i) + 1);

  return ret;
}

int main()
{
  freopen("LIS_1.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    memset(seq, -1, sizeof(seq));

    cin >> N;
    for (int x = 0; x < N; ++x)
      cin >> seq[x];

    cout << solve(-1) - 1 << endl;
  }
  return 0;
}