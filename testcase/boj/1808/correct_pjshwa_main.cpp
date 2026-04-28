#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
vector<int> adj[MAX];
int L[MAX];

void mkl(int v, int l) {
  L[v] = l;
  for (int u : adj[v]) mkl(u, l + 1);
}

int maxl(int v) {
  int ret = L[v];
  for (int u : adj[v]) ret = max(ret, maxl(u));
  return ret;
}

void ded(int v) {
  L[v]--;
  for (int u : adj[v]) ded(u);
}

void solve() {
  int N, H; cin >> N;
  for (int i = 0; i < N - 1; i++) {
    int u, v; cin >> u >> v;
    adj[u].push_back(v);
  }
  cin >> H;

  mkl(0, 0);
  int ans = 0;

  while (1) {
    int add = 0;

    vector<int> U;
    for (int i = 0; i < N; i++) {
      if (L[i] == 2) U.push_back(i);
    }

    for (int v : U) {
      int m = maxl(v);
      if (m > H) add++, ded(v);
    }

    if (add == 0) break;
    ans += add;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
