#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
vector<int> graph[MAX + 1];
ll coin[MAX + 1];
bool vis[MAX + 1];

ll dfs(int v) {
  vis[v] = true;
  multiset<ll> cvs;
  for (int d : graph[v]) {
    if (!vis[d]) {
      ll res = dfs(d);
      if (res) cvs.insert(res);
    }
  }

  if (coin[v]) return cvs.size() ? max(coin[v], *cvs.rbegin()) : coin[v];
  else {
    if (cvs.size() >= 2) {
      auto it = cvs.rbegin();
      return coin[v] = *it + *(++it);
    }
    else if (cvs.size() == 1) return *cvs.rbegin();
    else return 0;
  }
}

void solve() {
  int n, x;
  cin >> n;
  for (int i = 2; i <= n; i++) {
    cin >> x;
    graph[x].push_back(i);
  }
  for (int i = 1; i <= n; i++) cin >> coin[i];

  dfs(1);
  cout << accumulate(coin, coin + n + 1, 0LL) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
