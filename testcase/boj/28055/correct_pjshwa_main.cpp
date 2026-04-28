#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
vector<int> adj[MAX + 1];
ll ssz[MAX + 1];

void dfs(int v) {
  ssz[v] = 1;
  for (int u : adj[v]) {
    dfs(u);
    ssz[v] += ssz[u];
  }
}

void solve() {
  int n; cin >> n;
  for (int i = 2; i <= n; i++) {
    int p; cin >> p;
    adj[p].push_back(i);
  }

  dfs(1);
  sort(ssz + 1, ssz + n + 1);

  ll acc = 0; cout << "0 ";
  for (int i = 1; i <= n; i++) {
    acc += ssz[i] - 1;
    cout << acc << ' ';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
