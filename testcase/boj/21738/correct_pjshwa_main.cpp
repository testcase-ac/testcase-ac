#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e5, INF = 1e9 + 7;
vector<int> graph[MAX + 1];
int cdist[MAX + 1];

void solve() {
  int N, S, P;
  cin >> N >> S >> P;
  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  fill(cdist, cdist + N + 1, INF);
  queue<pii> q;
  q.push({P, 0});
  cdist[P] = 0;

  while (!q.empty()) {
    auto [v, c] = q.front();
    q.pop();

    for (auto &w : graph[v]) {
      if (cdist[w] == INF) {
        cdist[w] = c + 1;
        q.push({w, c + 1});
      }
    }
  }

  vector<int> r(S);
  for (int i = 1; i <= S; i++) r[i - 1] = cdist[i];
  sort(r.begin(), r.end());

  cout << N - r[0] - r[1] - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
