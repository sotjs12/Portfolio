#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

const long long NEGINF = numeric_limits<long long>::min();

int C, A, B;
const int MAX = 500;
int dp[MAX + 1][MAX + 1];
int seq[2][MAX + 1];

// Sub quest : x에서부터 시작하는 최대 증가 순열 길이 반환
// a 에서 시작하는 증가부분수열의 최대 길이
int solve(int a, int b)
{
  int &ret = dp[a + 1][b + 1];
  if (ret != -1)
    return ret;

  ret = 2;
  long long aValue = (a == -1) ? NEGINF : seq[0][a];
  long long bValue = (b == -1) ? NEGINF : seq[1][b];
  long long maxValue = max(aValue, bValue);

  for (int i = a + 1; i < A; ++i)
    if (maxValue < seq[0][i])
      ret = max(ret, solve(i, b) + 1);

  for (int i = b + 1; i < B; ++i)
    if (maxValue < seq[1][i])
      ret = max(ret, solve(a, i) + 1);

  return ret;
}

int main()
{
  freopen("JLIS.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    memset(dp, -1, sizeof(dp));
    memset(seq, -1, sizeof(seq));

    cin >> A >> B;
    for (int i = 0; i < A; ++i)
      cin >> seq[0][i];
    for (int i = 0; i < B; ++i)
      cin >> seq[1][i];

    cout << solve(-1, -1) - 2 << endl;
  }
  return 0;
}