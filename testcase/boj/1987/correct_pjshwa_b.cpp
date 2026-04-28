#include <iostream>
#include <cstdio>
#define endl '\n'
using namespace std;
char map[21][21];
bool check[26];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
int R, C;
int ans = 0;
int num[21][21];
void dfs(int x, int y, int d) {

  ans = max(ans, d);

    for (int i = 0; i < 4; i++) {

        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 1 || ny < 1 || nx > R || ny > C) continue;

        int alphabet = map[nx][ny] - 'A';
        if (check[alphabet]) continue;

        check[alphabet] = true;
        dfs(nx, ny, d + 1);
        check[alphabet] = false;
    }

}

int main(void) {

    scanf("%d %d ", &R, &C);
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            scanf(" %1c", &map[i][j]);
        }
    }

    check[map[1][1] - 'A'] = true;
    dfs(1, 1, 1);
    printf("%d\n", ans);
    return 0;
}

