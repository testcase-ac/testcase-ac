#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
vector<int> adj[MAXN];
ll ma[MAXN], mb[MAXN], Jinv[MAXN];
bool vis[MAXN];
map<ll, int> J; int ji;

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void add(ll item) {
  if (J.count(item)) return;
  J[item] = ji;
  Jinv[ji] = item;
  ji++;
}

void solve() {
  int N; cin >> N;

  vector<pii> W;
  for (int i = 0; i < N; ++i) {
    int x, y; cin >> x >> y;
    W.emplace_back(x, y);
  }
  for (int i = 0; i < N; ++i) {
    ll x = W[i].first, y = W[i].second;
    for (ll item : {x + y, x - y, x * y}) {
      add(item);
      adj[J[item]].push_back(i);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < ji; i++) {
    if (ma[i] != -1) continue;
    memset(vis, 0, sizeof vis);
    if (dfs(i)) ++match;
  }

  if (match < N) {
    cout << "impossible\n";
    return;
  }

  for (int i = 0; i < N; ++i) {
    assert(mb[i] != -1 && ma[mb[i]] == i);
    ll tar = Jinv[mb[i]], x = W[i].first, y = W[i].second;
    if (tar == x + y) cout << x << " + " << y << " = " << tar << "\n";
    else if (tar == x - y) cout << x << " - " << y << " = " << tar << "\n";
    else if (tar == x * y) cout << x << " * " << y << " = " << tar << "\n";
    else assert(false);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
