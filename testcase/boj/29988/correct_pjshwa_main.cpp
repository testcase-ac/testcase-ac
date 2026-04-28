#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int A[MAXN + 1];
vector<int> adj[MAXN + 1], L;
int change_from[MAXN + 1], change_to[MAXN + 1], ans[MAXN + 1];

void dfs(int v, int p) {
  if (L.empty() || A[v] > L.back()) {
    change_to[v] = A[v];
    L.push_back(A[v]);
  }
  else {
    auto it = lower_bound(L.begin(), L.end(), A[v]);
    change_from[v] = *it;
    *it = A[v];
    change_to[v] = *it;
  }
  ans[v] = L.size();

  // cout << "v = " << v << ", L = ";
  // for (int x : L) cout << x << ' ';
  // cout << '\n';

  for (int u : adj[v]) {
    if (u != p) dfs(u, v);
  }

  if (change_to[v] != -1) {
    if (change_from[v] == -1) L.pop_back();
    else {
      auto it = lower_bound(L.begin(), L.end(), change_to[v]);
      *it = change_from[v];
    }
  }
}

void solve() {
  int N; cin >> N;
  for (int i = 2; i <= N; ++i) {
    int p; cin >> p;
    adj[p].push_back(i); adj[i].push_back(p);
  }
  for (int i = 1; i <= N; ++i) cin >> A[i];

  memset(change_from, -1, sizeof(change_from));
  memset(change_to, -1, sizeof(change_to));
  dfs(1, 0);

  for (int i = 2; i <= N; ++i) cout << ans[i] << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
