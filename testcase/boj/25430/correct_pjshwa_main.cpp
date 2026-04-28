#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50'000, MAXV = 1e7;
vector<int> graph[MAX + 1];
ll cdist[MAX + 1];

void solve() {
  int N, M, s, e;
  cin >> N >> M;
  vector<tii> edges(M);
  for (int i = 0; i < M; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    edges[i] = {u, v, w};
  }
  sort(edges.begin(), edges.end(), [] (const tii& a, const tii& b) {
    return get<2>(a) < get<2>(b);
  });
  cin >> s >> e;

  fill(cdist, cdist + MAX + 1, 1e18);
  cdist[s] = 0;

  int vi = 0;
  for (int i = 0; i <= MAXV; i++) {
    map<int, ll> ndist;

    while (vi < M && get<2>(edges[vi]) <= i) {
      auto [u, v, w] = edges[vi];
      if (ndist.count(v)) ndist[v] = min(ndist[v], cdist[u] + w);
      else ndist[v] = cdist[u] + w;
      if (ndist.count(u)) ndist[u] = min(ndist[u], cdist[v] + w);
      else ndist[u] = cdist[v] + w;
      vi++;
    }

    for (auto [v, d] : ndist) {
      if (cdist[v] > d) cdist[v] = d;
    }
  }

  if (cdist[e] == 1e18) cout << "DIGESTA\n";
  else cout << cdist[e] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
