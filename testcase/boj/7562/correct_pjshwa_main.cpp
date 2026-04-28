#include <bits/stdc++.h>
#define pii pair<int, int>
#define piipi pair<pii, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

bool vis[300][300];
int main() {
  fast_io();

  int t, n, ax, ay, dx, dy, x, y, cnt;
  pii pos;

  cin >> t;
  queue<piipi> nq;

  while (t--) {
    cin >> n >> ax >> ay >> dx >> dy;
    nq.push({{ax, ay}, 0});

    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) vis[i][j] = false;
    }

    while (!nq.empty()) {
      tie(pos, cnt) = nq.front();
      tie(x, y) = pos;
      nq.pop();

      if (vis[x][y]) continue;
      vis[x][y] = true;

      if (x == dx && y == dy) {
        cout << cnt << '\n';
        break;
      }

      if (x + 1 < n && y + 2 < n && !vis[x + 1][y + 2]) nq.push({{x + 1, y + 2}, cnt + 1});
      if (x + 2 < n && y + 1 < n && !vis[x + 2][y + 1]) nq.push({{x + 2, y + 1}, cnt + 1});
      if (x + 2 < n && y - 1 >= 0 && !vis[x + 2][y - 1]) nq.push({{x + 2, y - 1}, cnt + 1});
      if (x + 1 < n && y - 2 >= 0 && !vis[x + 1][y - 2]) nq.push({{x + 1, y - 2}, cnt + 1});
      if (x - 1 >= 0 && y - 2 >= 0 && !vis[x - 1][y - 2]) nq.push({{x - 1, y - 2}, cnt + 1});
      if (x - 2 >= 0 && y - 1 >= 0 && !vis[x - 2][y - 1]) nq.push({{x - 2, y - 1}, cnt + 1});
      if (x - 2 >= 0 && y + 1 < n && !vis[x - 2][y + 1]) nq.push({{x - 2, y + 1}, cnt + 1});
      if (x - 1 >= 0 && y + 2 < n && !vis[x - 1][y + 2]) nq.push({{x - 1, y + 2}, cnt + 1});
    }

    // Empty queue
    while (!nq.empty()) nq.pop();
  }
}
