#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2000, MOD = 1e9 + 7;
vector<int> adj[MAX + 1];
int d[MAX + 1];

int r1(int v) {
  if (d[v] != -1) return d[v];
  if (v == 1) return d[v] = 1;

  int ret = 0;
  for (int u : adj[v]) ret = (ret + r1(u)) % MOD;
  return d[v] = ret;
}

int r2(int v) {
  if (d[v] != -1) return d[v];

  int ret = v == 1;
  for (int u : adj[v]) ret |= r2(u);
  return d[v] = ret;
}

void solve() {
  int N, L; cin >> N >> L;
  for (int i = 1; i <= L; i++) {
    int K; cin >> K;
    while (K--) {
      int x; cin >> x;
      adj[x].push_back(i);
    }
  }

  int ans1 = 0; memset(d, -1, sizeof(d));
  for (int i = L + 1; i <= N; i++) ans1 = (ans1 + r1(i)) % MOD;

  int ans2 = 0; memset(d, -1, sizeof(d));
  for (int i = L + 1; i <= N; i++) ans2 = (ans2 + r2(i)) % MOD;

  cout << ans1 << ' ' << ans2 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
