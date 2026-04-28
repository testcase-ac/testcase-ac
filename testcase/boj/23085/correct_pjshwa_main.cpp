#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3000;
bool vis[MAX + 1][MAX + 1];
int n, k;

int bfs(int s) {
  queue<tuple<int, int, int>> q;
  q.push({s, n - s, 0});
  vis[s][n - s] = true;

  while (!q.empty()) {
    auto [x, y, c] = q.front();
    q.pop();

    if (x == 0) return c;
    
    // How many heads are chosen?
    for (int i = 0; i <= k; i++) {
      if (i > x || k - i > y) continue;
      int nx = x + (k - 2 * i), ny = y - (k - 2 * i);
      if (vis[nx][ny]) continue;
      vis[nx][ny] = true;
      q.push({nx, ny, c + 1});
    }
  }

  return -1;
}

int main() {
  fast_io();

  string s;
  cin >> n >> k >> s;

  int cnt = 0;
  for (int i = 0; i < n; i++) if (s[i] == 'H') cnt++;
  cout << bfs(cnt) << '\n';
}
