#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>

using namespace std;

//TPS1
int C;
int N;
const int MAX = 8;
const double INF = numeric_limits<double>::max();
double dist[MAX][MAX];
bool visited[MAX];
vector<int> path;

double solve(double len)
{
    if (path.size() == N)
        return len;

    double ret = INF;
    for (int next = 0; next < N; ++next)
    {
        if (visited[next])
            continue;

        int cur = path.back();
        path.push_back(next);
        visited[next] = true;
        ret = min(ret, solve(len + dist[cur][next]));
        visited[next] = false;
        path.pop_back();
    }

    return ret;
}

int main()
{
    freopen("C_6_3.txt", "r", stdin);

    cin >> C;
    while (C--)
    {
        memset(dist, -1, sizeof(dist));
        memset(visited, false, sizeof(visited));
        path.clear();

        cin >> N;
        for (int y = 0; y < N; ++y)
        {
            for (int x = 0; x < N; ++x)
            {
                cin >> dist[y][x];
            }
        }

        double result = INF;
        for (int i = 0; i < N; ++i)
        {
            path.push_back(i);
            visited[i] = true;

            result = min(result, solve(0));

            path.pop_back();
            visited[i] = false;
        }
        printf("%.10f\n", result);
    }

    return 0;
}