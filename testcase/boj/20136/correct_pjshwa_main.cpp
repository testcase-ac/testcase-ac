#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5, INF = 1e9 + 7;
int pos[MAX + 1], a[MAX + 1];
bool in_use[MAX + 1];
vector<int> fusage[MAX + 1];

void solve() {
  int n, k;
  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    cin >> a[i];
    fusage[a[i]].push_back(i);
  }

  // Optimal cache eviction
  int ans = 0, use_count = 0;
  priority_queue<pii> pq;
  for (int i = 0; i < k; i++) {
    int v = a[i];

    if (use_count == n && !in_use[v]) {
      int u = pq.top().second;
      pq.pop();
      ans++;
      in_use[u] = false;
      use_count--;
    }

    if (pos[v] + 1 == fusage[v].size()) pq.push({INF, v});
    else pq.push({fusage[v][++pos[v]], v});
    if (!in_use[v]) in_use[v] = true, use_count++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
