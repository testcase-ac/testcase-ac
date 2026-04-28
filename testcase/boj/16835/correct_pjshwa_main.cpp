#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
vector<int> graph[MAX + 1];
int cdist[2][MAX + 1];

void solve() {
  int N, M, S, T;
  cin >> N >> M >> S >> T;
  while (M--) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  fill(cdist[0], cdist[0] + N + 1, INF);
  fill(cdist[1], cdist[1] + N + 1, INF);

  queue<pii> q;
  q.push({0, S});
  cdist[0][S] = 0;

  while (!q.empty()) {
    auto [p, v] = q.front(); q.pop();

    for (auto u : graph[v]) {
      if (cdist[1 - p][u] == INF) {
        cdist[1 - p][u] = cdist[p][v] + 1;
        q.push({1 - p, u});
      }
    }
  }

  if (cdist[0][T] == 2) cout << "2\n";
  else if (cdist[1][T] == INF) cout << "-1\n";
  else {
    int t = cdist[1][T];
    while (!is_prime(t)) t += 2;
    cout << t << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
