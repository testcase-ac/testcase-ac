#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int parent[MAX + 1];

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
  int n, m;
  cin >> n >> m;

  int cost[n + 1];
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < m; i++) {
    int ci, ai;
    cin >> ci >> ai;
    pq.push({ai, ci});
  }
  for (int i = 1; i <= n; i++) cin >> cost[i], parent[i] = i;

  ll ans = 0;
  while (!pq.empty()) {
    auto [ai, ci] = pq.top();
    pq.pop();

    if (Find(0) == Find(ci)) continue;
    ans += ai;
    Union(0, ci);

    int pci = ci - 1, nci = ci + 1;
    if (pci == 0) pci = n;
    if (nci == n + 1) nci = 1;

    pq.push({cost[pci], pci});
    pq.push({cost[ci], nci});
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
