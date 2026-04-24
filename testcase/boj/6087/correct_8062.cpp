#include <iostream>
#include <vector>
#include <queue>

int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};

using namespace std;

int main()
{
    int C, R;
    const int MX = 1e9;
    cin >> C >> R;
    vector<string> arr(R);
    vector<vector<int>> cost(R, vector<int>(C, MX));

    for (int i = 0; i < R; i++)
    {
        cin >> arr[i];
    }
    int r1 = -1, c1 = -1, r2 = -1, c2 = -1;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (arr[i][j] == 'C') {
                if (r1 == -1) {
                    r1 = i;
                    c1 = j;
                } else {
                    r2 = i;
                    c2 = j;
                }
            }
        }
    }
    cost[r1][c1] = 0;
    queue<pair<int, int>> q;
    q.push({r1, c1});
    while (!q.empty()) {
        auto cur = q.front();
        q.pop();
        int cr = cur.first;
        int cc = cur.second;
        for (int dir = 0; dir < 4; dir++) {
            int nr = cr + dr[dir];
            int nc = cc + dc[dir];
            while (nr >= 0 && nr < R && nc >= 0 && nc < C && arr[nr][nc] != '*') {
                if (cost[nr][nc] > cost[cr][cc] + 1) {
                    cost[nr][nc] = cost[cr][cc] + 1;
                    q.push({nr, nc});
                }
                nr += dr[dir];
                nc += dc[dir];
            }
        }
    }
    cout << cost[r2][c2] - 1 << '\n';
}
