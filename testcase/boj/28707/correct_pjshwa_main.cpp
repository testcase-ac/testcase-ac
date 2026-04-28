#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  int A[N]; for (int i = 0; i < N; ++i) cin >> A[i];

  vector<int> p(N); iota(p.begin(), p.end(), 0);
  map<vector<int>, int> cdist;

  auto is_monotonic_inc = [&](vector<int>& v) {
    for (int i = 1; i < N; ++i) {
      if (A[v[i - 1]] > A[v[i]]) return false;
    }
    return true;
  };

  priority_queue<pair<int, vector<int>>, vector<pair<int, vector<int>>>, greater<pair<int, vector<int>>>> pq;
  do {
    if (is_monotonic_inc(p)) {
      cdist[p] = 0;
      pq.emplace(0, p);
    }
  } while (next_permutation(p.begin(), p.end()));

  int M; cin >> M;
  vector<tuple<int, int, int>> edges;
  while (M--) {
    int u, v, w; cin >> u >> v >> w;
    edges.emplace_back(u - 1, v - 1, w);
  }

  while (!pq.empty()) {
    auto [dist, vec] = pq.top(); pq.pop();
    if (cdist[vec] < dist) continue;
    for (auto [u, v, w] : edges) {
      swap(vec[u], vec[v]);
      if (cdist.find(vec) == cdist.end() || cdist[vec] > dist + w) {
        cdist[vec] = dist + w;
        pq.emplace(dist + w, vec);
      }
      swap(vec[u], vec[v]);
    }
  }

  vector<int> ini(N); iota(ini.begin(), ini.end(), 0);
  if (cdist.find(ini) == cdist.end()) cout << "-1\n";
  else cout << cdist[ini] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
