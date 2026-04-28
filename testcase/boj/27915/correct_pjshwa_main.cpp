#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
vector<int> adj[MAX + 1];
int O, E;

void dfs(int v, int l) {
  if (l & 1) O++;
  else E++;

  for (int u : adj[v]) dfs(u, l + 1);
}

void solve() {
  int N; cin >> N;
  for (int i = 2; i <= N; i++) {
    int p; cin >> p;
    adj[p].push_back(i);
  }
  dfs(1, 0);
  cout << max(O, E) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
