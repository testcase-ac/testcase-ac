#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
bool vis[8][8];

int main() {
  fast_io();

  int si, sj, ei, ej;
  cin >> si >> sj >> ei >> ej;

  queue<tii> q;
  q.push({si - 1, sj - 1, 0});
  vis[si - 1][sj - 1] = true;

  while (!q.empty()) {
    auto [i, j, cnt] = q.front();
    q.pop();

    if (i == ei - 1 && j == ej - 1) return cout << cnt << '\n', 0;

    for (int k = 0; k < 8; k++) {
      int nx = i + dx[k], ny = j + dy[k];
      if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8 || vis[nx][ny]) continue;
      q.push({nx, ny, cnt + 1});
      vis[nx][ny] = true;
    }
  }
}
