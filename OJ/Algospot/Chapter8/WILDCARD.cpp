#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

int C, N;
string P, S;
const int MAX_P = 100, MAX_S = 100;
int dp[MAX_P + 1][MAX_S + 1];

bool solve(int p, int s)
{
  int &ret = dp[p][s];
  if (ret != -1)
    return ret;

  if (p < P.size() && s < S.size() && (P[p] == '?' || S[s] == P[p]))
    return ret = solve(p + 1, s + 1);

  if (p == P.size())
    return ret = (s == S.size());

  if (P[p] == '*')
  {
    if (solve(p + 1, s) || (s < S.size() && solve(p, s + 1)))
      return ret = true;
  }

  return ret = false;
}

int main()
{
  freopen("WILDCARD.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    vector<string> results;

    cin >> P;
    cin >> N;

    while (N--)
    {
      memset(dp, -1, sizeof(dp));
      cin >> S;
      if (solve(0, 0))
        results.push_back(S);
    }

    sort(results.begin(), results.end());
    for (int i = 0; i < results.size(); ++i)
      cout << results[i] << endl;
  }
  return 0;
}