#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int MAX = 1e5, MOD = 1e9 + 7;
vector<int> graph[MAX + 1];
int a[MAX + 1];
int tcnt[MAX + 1], fcnt[MAX + 1];
bool vis[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll res = 0;
void dfs(int v) {
  res += fcnt[a[v]];
  for (int i = 1; i * i <= a[v]; i++) {
    if (a[v] % i) continue;
    res += tcnt[i];
    fcnt[i]++;
    if (i * i != a[v]) {
      res += tcnt[a[v] / i];
      fcnt[a[v] / i]++;
    }
  }
  res -= tcnt[a[v]];
  tcnt[a[v]]++;

  for (int d : graph[v]) dfs(d);

  tcnt[a[v]]--;
  for (int i = 1; i * i <= a[v]; i++) {
    if (a[v] % i) continue;
    fcnt[i]--;
    if (i * i != a[v]) {
      fcnt[a[v] / i]--;
    }
  }
}

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  for (int i = 2; i <= n; i++) {
    int x;
    cin >> x;
    graph[x].push_back(i);
  }
  dfs(1);
  cout << res << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
