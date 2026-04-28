#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 100;
const ll INF = 1e18;
vector<tii> graph[MAX + 1];
ll cdist[MAX + 1][10001];
int n, m;

void dijk(int s) {
  for (int i = 1; i <= n; i++) for (int j = 0; j <= m; j++) cdist[i][j] = INF;
  cdist[s][0] = 0;

  priority_queue<tii, vector<tii>, greater<tii>> pq;
  pq.push({0, s, 0});

  while (!pq.empty()) {
    auto [wi, ui, mi] = pq.top();
    pq.pop();

    if (wi > cdist[ui][mi]) continue;

    for (auto [vi, ci, di] : graph[ui]) {
      if (mi + ci <= m && cdist[vi][mi + ci] > wi + di) {
        cdist[vi][mi + ci] = wi + di;
        pq.push({cdist[vi][mi + ci], vi, mi + ci});
      }
    }
  }
}

void solve() {
  int k;
  cin >> n >> m >> k;

  for (int i = 1; i <= n; i++) graph[i].clear();
  while (k--) {
    int ai, bi, ci, di;
    cin >> ai >> bi >> ci >> di;
    graph[ai].push_back({bi, ci, di});
  }

  dijk(1);
  ll ans = INF;
  for (int i = 0; i <= m; i++) ans = min(ans, cdist[n][i]);
  if (ans == INF) cout << "Poor KCM\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
