#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, MOD = 1e9 + 7;
vector<int> graph[MAX + 1];
int parent[MAX + 1], level[MAX + 1];
string v[MAX + 1];
bool vis[MAX + 1];

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

void dfs(int node, int lv) {
  vis[node] = true;
  level[node] = lv;

  for (int el : graph[node]) {
    if (!vis[el]) {
      parent[el] = node;
      dfs(el, lv + 1);
    }
  }
}

void solve() {
  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; i++) cin >> v[i];
  for (int i = 0; i < n - 1; i++) {
    int x, y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  // fill parent array
  dfs(1, 0);

  while (q--) {
    int x, y;
    cin >> x >> y;

    vector<string> front, back;
    while (x != y) {
      if (level[x] < level[y]) {
        back.push_back(v[y]);
        y = parent[y];
      }
      else {
        front.push_back(v[x]);
        x = parent[x];
      }
    }
    front.push_back(v[x]);
    while (!back.empty()) {
      front.push_back(back.back());
      back.pop_back();
    }

    ll res = 0;
    for (string s : front) {
      res = (res * lpow(10, s.size(), MOD)) % MOD;
      res = (res + stoi(s)) % MOD;
    }
    cout << res << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
