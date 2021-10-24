#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int C, N, S, IN;
const int MAX = 100;
const int INF = 987654321;

int dp[MAX + 1][MAX + 1];
vector<int> arr;
int sum[MAX + 1];
int sumD[MAX + 1];

int minError(int a, int b)
{
  int subSum = sum[b] - (a == 0 ? 0 : sum[a - 1]);
  int avg = int(0.5 + ((double)subSum / (b - a + 1)));
  int sq = sumD[b] - (a == 0 ? 0 : sumD[a - 1]);
  return sq - (2 * avg * subSum) + (avg * avg * (b - a + 1));
}
//idx 번째에서 S개의 부분들의 최소합
int solve(int p, int s)
{
  if (p == N)
    return 0;
  if (s == 0)
    return INF;

  int &ret = dp[p][s];
  if (ret != -1)
    return ret;

  ret = INF;

  for (int i = 1; i <= N - p; ++i)
    ret = min(ret, minError(p, p + i - 1) + solve(p + i, s - 1));

  return ret;
}

int main()
{
  freopen("QUANTIZE.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    arr.clear();
    cin >> N >> S;
    for (int i = 0; i < N; ++i)
    {
      cin >> IN;
      arr.push_back(IN);
    }

    sort(arr.begin(), arr.end());
    sum[0] = arr[0];
    sumD[0] = arr[0] * arr[0];
    for (int i = 1; i < N; ++i)
    {
      sum[i] = sum[i - 1] + arr[i];
      sumD[i] = sumD[i - 1] + (arr[i] * arr[i]);
    }
    cout << solve(0, S) << endl;
  }

  return 0;
}