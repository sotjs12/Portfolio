#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

const int dx_0[8] = {0, 1, 1, 1, 0, -1, -1, -1};
const int dy_0[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int size_0 = 5;
int dp_0[size_0][size_0][10];

bool hasWord(vector<string> board, int y, int x, string &word, int idx)
{
    if (y < 0 || y >= size_0 || x < 0 || x >= size_0)
        return false;
    if (word[idx] != board[y][x])
        return false;
    if (idx == word.size() - 1)
        return true;

    int &ret = dp_0[y][x][idx];
    if (ret != -1)
        return ret;

    ret = 0;
    for (int i = 0; i < 8 && !ret; ++i)
        ret = hasWord(board, y + dy_0[i], x + dx_0[i], word, idx + 1);

    return ret;
}
void BOGGLE()
{
    int caseCnt = 0;
    vector<string> board;

    cin >> caseCnt;

    while (caseCnt--)
    {
        board.clear();
        int mapCnt = size_0, quizCnt;
        string word;

        while (mapCnt--)
        {
            cin >> word;
            board.push_back(word);
        }

        cin >> quizCnt;
        while (quizCnt--)
        {
            memset(dp_0, -1, sizeof(dp_0));
            bool success = false;
            cin >> word;
            for (int y = 0; y < size_0 && !success; ++y)
                for (int x = 0; x < size_0 && !success; ++x)
                    success = hasWord(board, y, x, word, 0);
            cout << word << " " << (success ? "YES" : "NO") << endl;
        }
    }
}

int main()
{
    BOGGLE();
    return 0;
}