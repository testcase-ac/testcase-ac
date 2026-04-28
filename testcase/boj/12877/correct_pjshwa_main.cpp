#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50000;
int parent[MAX + 1], type[MAX + 1];
set<int> g[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y, int t) {
  int ox = x, oy = y;

  x = Find(x);
  y = Find(y);

  if (x == y) return;

  int xsz = g[x].size(), ysz = g[y].size();
  if (xsz > ysz) {
    parent[y] = x;
    int dt = (type[ox] - type[oy] + t + 3) % 3;
    for (int e : g[y]) {
      g[x].insert(e);
      type[e] = (type[e] + dt) % 3;
    }
    g[y].clear();
  }
  else {
    parent[x] = y;
    int dt = (type[oy] - type[ox] - t + 6) % 3;
    for (int e : g[x]) {
      g[y].insert(e);
      type[e] = (type[e] + dt) % 3;
    }
    g[x].clear();
  }
}

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 1; i <= N; i++) parent[i] = i, g[i].insert(i);

  int ans = 0;
  for (int i = 0; i < K; i++) {
    int op, x, y;
    cin >> op >> x >> y;
    if (x < 1 || x > N || y < 1 || y > N) {
      ans++;
      continue;
    }

    if (op == 1) {
      if (Find(x) == Find(y)) {
        if (type[x] == type[y]) continue;
        else ans++;
      }
      else Union(x, y, 0);
    }
    if (op == 2) {
      if (Find(x) == Find(y)) {
        int yt = (type[x] + 1) % 3;
        if (yt == type[y]) continue;
        else ans++;
      }
      else Union(x, y, 1);
    }
  }

  for (int i = 1; i <= 10; i++) {
    // cout << "i = " << i << ", type[i] = " << type[i] << endl;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
