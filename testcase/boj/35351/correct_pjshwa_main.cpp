#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6;
int parent[MAXN], dp[MAXN];
vector<int> adj[MAXN];

int rec(int u) {
  if (dp[u] != -1) return dp[u];
  int cnt = 0;
  for (int v : adj[u]) cnt += rec(v);
  return dp[u] = cnt > 1;
}

void solve() {
  int t, Q, N = 1; string S; cin >> t >> Q >> S;

  int it = 0; queue<int> q; q.push(it);
  for (int l = 0; l < t; ++l) {
    queue<int> nq;
    while (!q.empty()) {
      int u = q.front(); q.pop();
      for (int j = 0; j < 3; ++j) {
        ++it;
        adj[u].push_back(it);
        parent[it] = u;
        nq.push(it);
      }
    }
    while (!nq.empty()) q.push(nq.front()), nq.pop();
    N *= 3;
  }

  memset(dp, -1, sizeof(dp));
  for (int i = 0; i < N; ++i) dp[it - i] = S[N - 1 - i] - 'A';

  while (Q--) {
    int i; cin >> i;
    int u = it - N + i;
    dp[u] ^= 1;
    while (u > 0) {
      dp[parent[u]] = -1;
      u = parent[u];
    }
    cout << (char)(rec(0) + 'A') << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
