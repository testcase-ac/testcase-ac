#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX + 1];
vector<int> graph[MAX + 1];
int d[MAX + 1];

int dfs(int v) {
  int ssum = a[v];
  for (int u : graph[v]) {
    int val = dfs(u);
    if (val > 0) ssum += val;
  }
  return d[v] = ssum;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int p;
    cin >> p >> a[i];
    graph[p].push_back(i);
  }

  dfs(1);
  cout << *max_element(d + 1, d + n + 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
