#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10, INF = 1e9 + 7;
int b[MAX + 1], deg[MAX + 1], parent[MAX + 1];
tii edges[30];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int n, m;
  cin >> n >> m;
  if (m < n - 1) return cout << "NO\n", void();

  for (int i = 1; i <= n; i++) cin >> b[i];
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    edges[i] = {x, y, w};
  }

  int ans = INF;
  vector<int> ansv;
  int stack[30];
  bool finished;

  // combinations
  int stack_pointer = -1, c = n - 1;
  stack[0] = 0;

  finished = false;
  while (!finished) {

    for (stack_pointer++; stack_pointer < c - 1; stack_pointer++) {
      stack[stack_pointer + 1] = stack[stack_pointer] + 1;
    }

    // stack[0]..stack[c - 1] contains the indexes
    // do work here

    for (int i = 1; i <= n; i++) parent[i] = i, deg[i] = 0;

    int uc = 0, wgt = 0;
    vector<int> cur(c);
    for (int i = 0; i < c; i++) cur[i] = stack[i];
    for (int i = 0; i < c; i++) {
      auto [x, y, w] = edges[cur[i]];
      if (Find(x) != Find(y)) {
        Union(x, y);
        uc++; deg[x]++; deg[y]++;
        wgt += w;
      }
    }

    bool able = true;
    for (int i = 1; i <= n; i++) able &= deg[i] <= b[i];
    if (able && uc == n - 1 && wgt < ans) {
      ans = wgt;
      ansv = cur;
    }

    // do work here

    do {
      if (stack_pointer == -1) {
        finished = true;
        break;
      }
      stack[stack_pointer--]++;
    } while (stack[stack_pointer + 1] + c == m + stack_pointer + 2);
  }

  if (ans == INF) cout << "NO\n";
  else {
    cout << "YES\n";
    for (int i : ansv) {
      auto [x, y, w] = edges[i];
      cout << min(x, y) << ' ' << max(x, y) << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
