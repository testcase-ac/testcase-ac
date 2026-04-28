#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5;
vector<int> adj[MAX + 1];
int R[MAX + 1], G[MAX + 1], B[MAX + 1];
int d[MAX + 1][3];
char A[MAX + 10];

int r(int i, int p, int c) {
  if (d[i][c] != -1) return d[i][c];

  int acc = 0, val = c == 0 ? R[i] : c == 1 ? G[i] : B[i];
  for (int u : adj[i]) {
    if (u == p) continue;

    int chd = 0;
    for (int x : {0, 1, 2}) {
      if (x == c) continue;
      chd = max(chd, r(u, i, x));
    }
    acc += chd;
  }
  return d[i][c] = acc + val;
}

void trace(int i, int p, int c) {
  A[i] = c == 0 ? 'R' : c == 1 ? 'G' : 'B';
  for (int u : adj[i]) {
    if (u == p) continue;

    int chd = 0;
    for (int x : {0, 1, 2}) {
      if (x == c) continue;
      chd = max(chd, d[u][x]);
    }
    for (int x : {0, 1, 2}) {
      if (x == c) continue;
      if (d[u][x] == chd) {
        trace(u, i, x);
        break;
      }
    }
  }
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  for (int i = 1; i <= N; i++) cin >> R[i] >> G[i] >> B[i];

  memset(d, -1, sizeof(d));

  int ans = 0;
  for (int i = 0; i < 3; i++) ans = max(ans, r(1, -1, i));
  cout << ans << '\n';

  for (int i = 0; i < 3; i++) {
    if (d[1][i] == ans) {
      A[1] = i == 0 ? 'R' : i == 1 ? 'G' : 'B';
      trace(1, -1, i);
    }
  }
  cout << A + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
