#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 300;
int parent[MAX + 1];
int cost[MAX + 1][MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

void solve() {
  int n;
  cin >> n;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    pq.push({x, i});
    parent[i] = i;
  }
  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) cin >> cost[i][j];

  ll ans = 0;
  while (!pq.empty()) {
    auto [ai, ci] = pq.top();
    pq.pop();

    if (Find(0) == Find(ci)) continue;
    ans += ai;
    Union(0, ci);

    for (int i = 1; i <= n; i++) if (i != ci) pq.push({cost[ci][i], i});
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
