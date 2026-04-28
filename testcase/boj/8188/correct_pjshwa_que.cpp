#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
queue<int> by_val[MAX + 1], B[MAX + 1];
int U[MAX + 1];

void solve() {
  int m; cin >> m;
  vector<int> a(m);
  for (int i = 0; i < m; i++) cin >> a[i];

  int n; cin >> n;
  for (int i = 0; i < n; i++) {
    int l; cin >> l;
    for (int j = 0; j < l; j++) {
      int x; cin >> x;
      B[i].push(x);
    }
    int f = B[i].front(); B[i].pop();
    by_val[f].push(i);
  }

  queue<pii> nqueue;
  for (int x : a) {
    while (!by_val[x].empty()) {
      int i = by_val[x].front(); by_val[x].pop();
      if (B[i].empty()) continue;

      int f = B[i].front(); B[i].pop();
      nqueue.push({f, i});
    }

    while (!nqueue.empty()) {
      auto [f, i] = nqueue.front(); nqueue.pop();
      by_val[f].push(i);
    }
  }

  fill(U, U + n, 1);
  for (int v = 0; v <= MAX; v++) {
    while (!by_val[v].empty()) {
      int i = by_val[v].front(); by_val[v].pop();
      U[i] = 0;
    }
  }
  for (int i = 0; i < n; i++) {
    U[i] &= B[i].empty();
    cout << (U[i] ? "TAK" : "NIE") << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
