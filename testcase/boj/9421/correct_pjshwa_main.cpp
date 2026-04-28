#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 2e6;
int lp[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool vis[501], happy[501];

void dfs(int num) {
  vis[num] = 1;
  string s = to_string(num);
  int nxt = 0;
  for (char c : s) nxt += (c - '0') * (c - '0');
  if (!vis[nxt]) dfs(nxt);
}

void solve() {
  int n;
  cin >> n;
  for (int i = 3; i <= n; i++) {
    if (lp[i] == i) {
      string s = to_string(i);
      int nxt = 0;
      for (char c : s) nxt += (c - '0') * (c - '0');
      if (happy[nxt]) cout << i << '\n';
    }
  }
}

int main() {
  fast_io();

  vector<int> pr;

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  for (int i = 1; i <= 500; i++) {
    memset(vis, 0, sizeof(vis));
    dfs(i);
    if (vis[1]) happy[i] = 1;
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
