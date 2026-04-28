#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<int> adj[MAXN + 1];
int dp[MAXN + 1];

int rec(int v) {
  if (dp[v] != -1) return dp[v];

  int fr = 0, se = 0;
  for (int u : adj[v]) {
    int x = rec(u);
    if (x > fr) {
      se = fr;
      fr = x;
    }
    else if (x > se) {
      se = x;
    }
  }

  int ret = max(fr, se + 1);
  return dp[v] = ret;
}

void solve() {
  int n; cin >> n;
  for (int i = 1; i <= n; ++i) adj[i].clear();
  for (int i = 1; i <= n; ++i) {
    int x; cin >> x;
    if (x == 0) continue;
    adj[x].push_back(i);
  }

  fill(dp, dp + n + 1, -1);
  cout << rec(1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
