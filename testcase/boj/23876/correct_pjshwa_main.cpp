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

ll score(int i, int j) {
  return (ll)(j - i) * (j - i);
}

void solve() {
  int N, M; cin >> N >> M;

  iota(parent + 1, parent + N + 1, 1);
  while (M--) {
    int u, v; cin >> u >> v;
    Union(u, v);
  }
  if (Find(1) == Find(N)) return cout << "0\n", void();

  vector<int> SS, ES;
  for (int i = 1; i <= N; i++) {
    if (Find(i) == Find(1)) SS.push_back(i);
    if (Find(i) == Find(N)) ES.push_back(i);
  }

  ll ans = 1e18;
  for (int e : SS) {
    auto it = lower_bound(ES.begin(), ES.end(), e);
    if (it != ES.end()) ans = min(ans, score(e, *it));
    if (it != ES.begin()) ans = min(ans, score(e, *prev(it)));
  }

  map<int, ll> sdist, edist; set<int> groups;
  for (int i = 1; i <= N; i++) {
    int g = Find(i);
    if (g == Find(1) || g == Find(N)) continue;

    groups.insert(g);
    auto it1 = lower_bound(SS.begin(), SS.end(), i);
    auto it2 = lower_bound(ES.begin(), ES.end(), i);
    if (it1 != SS.end()) {
      if (sdist.count(g) == 0) sdist[g] = score(i, *it1);
      else sdist[g] = min(sdist[g], score(i, *it1));
    }
    if (it1 != SS.begin()) {
      if (sdist.count(g) == 0) sdist[g] = score(i, *prev(it1));
      else sdist[g] = min(sdist[g], score(i, *prev(it1)));
    }
    if (it2 != ES.end()) {
      if (edist.count(g) == 0) edist[g] = score(i, *it2);
      else edist[g] = min(edist[g], score(i, *it2));
    }
    if (it2 != ES.begin()) {
      if (edist.count(g) == 0) edist[g] = score(i, *prev(it2));
      else edist[g] = min(edist[g], score(i, *prev(it2)));
    }
  }

  for (int g : groups) {
    ans = min(ans, sdist[g] + edist[g]);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
