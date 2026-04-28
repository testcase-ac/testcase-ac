#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int ans;

void dfs(int v) {
  for (int d : graph[v]) {
    ans--;
    dfs(d);
  }
}

void solve() {
  int n;
  cin >> n;

  ans = 2 * (n - 1);
  for (int i = 0; i < n; i++) {
    int a, b, c;
    cin >> a >> b >> c;
    if (c != -1) graph[a].push_back(c);
  }
  dfs(1);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
