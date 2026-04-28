#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
int a[MAX], cdist[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n - 1; i++) cin >> a[i];

  fill(cdist, cdist + MAX, -1);

  queue<pii> q;
  q.push({0, 0});
  cdist[0] = 0;

  while (!q.empty()) {
    auto [x, c] = q.front();
    q.pop();

    for (int i = 1; i <= n - 1; i++) {
      int y = (x + i) % n;

      if (x > y && a[x - y] > 0) {
        if (cdist[y] == -1 || cdist[y] > c + a[x - y]) {
          cdist[y] = c + a[x - y];
          q.push({y, cdist[y]});
        }
      }
      if (x < y && a[x - y + n] > 0) {
        if (cdist[y] == -1 || cdist[y] > c + a[x - y + n]) {
          cdist[y] = c + a[x - y + n];
          q.push({y, cdist[y]});
        }
      }
    }
  }

  int m;
  cin >> m;
  while (m--) {
    int u, v;
    cin >> u >> v;
    int d = v - u;
    if (d < 0) d += n;
    cout << cdist[d] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
