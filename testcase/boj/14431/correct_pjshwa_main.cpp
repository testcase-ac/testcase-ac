#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

const int MAX = 4000;
const ll INF = 1e14;
ll cdist[MAX + 10];
pii pts[MAX + 10];
bool vis[MAX + 10];
int lp[MAX + 1];
vector<int> pr;
int v;

int dist(pii p1, pii p2) {
  return sqrt((p1.first - p2.first) * (p1.first - p2.first) +
              (p1.second - p2.second) * (p1.second - p2.second));
}

void dijk(int s) {
  fill(cdist, cdist + MAX + 10, INF);
  memset(vis, 0, sizeof(vis));
  cdist[s] = 0;

  for (int it = 1; it <= v - 1; it++) {
    ll md = INF, mi = -1;
    for (int vi = 1; vi <= v; vi++) {
      if (!vis[vi] && cdist[vi] <= md) {
        md = cdist[vi];
        mi = vi;
      }
    }

    vis[mi] = true;
    for (int vi = 1; vi <= v; vi++) {
      int d = dist(pts[mi], pts[vi]);
      if (lp[d] != d) continue;
      if (!vis[vi] && cdist[mi] + d < cdist[vi]) {
        cdist[vi] = cdist[mi] + d;
      }
    }
  }
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  pii s, e;
  cin >> s.first >> s.second >> e.first >> e.second >> v;

  for (int vi = 1; vi <= v; vi++) cin >> pts[vi].first >> pts[vi].second;
  pts[++v] = e;
  pts[++v] = s;
  dijk(v);
  cout << (cdist[v - 1] == INF ? -1 : cdist[v - 1]) << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }
  lp[0] = lp[1] = -1;

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
