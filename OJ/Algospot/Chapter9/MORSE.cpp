#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N, M, K;
const int MAX = 100;
const int MAX_K = 1000000000 + 100;
int dp[MAX + 1][MAX + 1];
int bino[201][201];
int skip = 0;

void calcBino()
{
  memset(bino, 0, sizeof(bino));
  for (int i = 0; i <= 200; ++i)
  {
    bino[i][0] = bino[i][i] = 1;
    for (int j = 1; j < i; ++j)
    {
      bino[i][j] = min(MAX_K, bino[i - 1][j - 1] + bino[i - 1][j]);
    }
  }
}

void solve(int n, int m, string s)
{
  if (skip < 0)
    return;
  if (n == 0 && m == 0)
  {
    if (skip == 0)
      cout << s << endl;
    --skip;
    return;
  }
  if (bino[n + m][n] <= skip)
  {
    skip -= bino[n + m][n];
    return;
  }
  if (n > 0)
    solve(n - 1, m, s + "-");
  if (m > 0)
    solve(n, m - 1, s + "o");
}

string solve2(int n, int m, int s)
{
  if (n == 0)
    return string(m, 'o');
  if(m==0) return string(n,'-');

  if (skip <= bino[n + m - 1][n - 1])  
    return "-" + solve2(n - 1, m, s);  
  return "o" + solve2(n, m - 1, s - bino[n + m - 1][n - 1]);
}

int main()
{
  freopen("MORSE.txt", "r", stdin);
  calcBino();
  cin >> C;
  while (C--)
  {
    cin >> N >> M >> K;
    skip = K - 1;
    cout << solve2(N, M, skip) << endl;
    // solve(N, M, "");
  }

  return 0;
}