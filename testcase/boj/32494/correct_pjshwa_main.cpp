#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int parent[MAXN + 1], usz[MAXN + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    return parent[x] = p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x == y) return;

  parent[y] = x;
  usz[x] += usz[y];
}

void solve() {
  int N, Q; cin >> N >> Q;
  iota(parent, parent + N + 1, 0);
  fill(usz, usz + N + 1, 1);

  vector<tuple<int, int, int>> edges; set<int> ws;
  for (int i = 0; i < N - 1; ++i) {
    int u, v, w; cin >> u >> v >> w;
    edges.emplace_back(w, u, v);
    ws.insert(w);
  }
  sort(edges.begin(), edges.end());

  ll ei = 0, tsum = 0, csum = 0, psum = 0;
  map<int, ll> w2p;
  for (auto& cw : ws) {
    while (ei < N - 1) {
      auto [w, u, v] = edges[ei];
      if (w > cw) break;

      u = Find(u), v = Find(v);
      assert(u != v);

      csum += (ll)usz[u] * usz[v];
      Union(u, v); ++ei;
    }
    tsum += (csum - psum) * cw;
    w2p[cw] = tsum;
    psum = csum;
  }

  int minw = *ws.begin(), maxw = *ws.rbegin();
  while (Q--) {
    int l, r; cin >> l >> r;
    if (r < minw || l > maxw) {
      cout << "0\n";
      continue;
    }

    auto itl = w2p.upper_bound(l - 1);
    auto itr = w2p.upper_bound(r);
    assert(itr != w2p.begin());
    --itr;

    if (itl == w2p.begin()) cout << itr->second << '\n';
    else {
      --itl;
      cout << (itr->second - itl->second) << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
