#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

int C, N, W;
const int MAX_N = 1000;
const int MAX_W = 1000;
int dp[MAX_W + 1][MAX_N + 1];
int arr[MAX_N + 1][2];
string s_arr[MAX_N + 1];
vector<string> result;

// W 부피에 item 부터 얻을수있는 최대 절박합
int pack(int w, int item)
{
  if (item == N)
    return 0;
  int &ret = dp[w][item];
  if (ret != -1)
    return ret;
  ret = pack(w, item + 1);
  if (arr[item][0] <= w)
    ret = max(ret, pack(w - arr[item][0], item + 1) + arr[item][1]);

  return ret;
}

void solve(int w, int item)
{
  if (item == N)
    return;

  if (pack(w, item) != pack(w, item + 1))
  {
    result.push_back(s_arr[item]);
    solve(w - arr[item][0], item + 1);
  }
  else
  {
    solve(w, item + 1);
  }
}

int main()
{
  freopen("PACKING.txt", "r", stdin);
  cin >> C;
  while (C--)
  {
    result.clear();
    memset(dp, -1, sizeof(dp));
    cin >> N >> W;
    for (int i = 0; i < N; ++i)
      cin >> s_arr[i] >> arr[i][0] >> arr[i][1];

    int max = pack(W, 0);
    solve(W, 0);

    cout << max << " " << result.size() << endl;
    for (int i = 0; i < result.size(); ++i)
      cout << result[i] << endl;
  }

  return 0;
}