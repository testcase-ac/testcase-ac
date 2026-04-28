#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
vector<int> graph[MAX + 1];
ll p[MAX + 1], vs[MAX + 1], ve[MAX + 1], par[MAX + 1], deg[MAX + 1], ord[MAX + 1];
bool vis[MAX + 1];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __update(int si, int ss, int se, int p, ll val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    tree[si] = tree[left] + tree[right];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

void print(ll cur) {
  cout << cur / 10000 << '.';
  string rem = to_string(cur % 10000);
  while (rem.size() < 4) rem = "0" + rem;
  cout << rem << '\n';
}

void solve() {
  int N;
  cin >> N;

  ll cur = 0;
  for (int i = 1; i <= N; i++) {
    double x;
    cin >> x;
    p[i] = (ll)(x * 10000 + 0.5);
    cur += p[i];
  }

  for (int i = 0; i < N - 1; i++) {
    int u, v;
    cin >> u >> v;
    graph[u].push_back(v);
    graph[v].push_back(u);
    deg[u]++;
    deg[v]++;

    cur += p[u] + p[v];
    cur -= 2 * (p[u] / 100) * (p[v] / 100);
  }

  queue<int> q;
  q.push(1);
  vis[1] = true;
  par[1] = -1;
  ord[1] = 1;

  int tick = 1;
  while (!q.empty()) {
    int v = q.front();
    q.pop();

    vs[ord[v]] = tick;
    for (int d : graph[v]) {
      if (vis[d]) continue;

      vis[d] = true;
      ord[d] = ++tick;
      par[ord[d]] = ord[v];
      q.push(d);
    }
    ve[ord[v]] = tick;
  }

  vector<int> tmp(N + 1);
  for (int i = 1; i <= N; i++) tmp[i] = p[i];
  for (int i = 1; i <= N; i++) p[ord[i]] = tmp[i];

  for (int i = 1; i <= N; i++) {
    // cout << "vs[i] = " << vs[i] << " ve[i] = " << ve[i] << ", p[i] = " << p[i] << '\n';
  }

  SegmentTree s(N + 1);
  for (int i = 1; i <= N; i++) s.update(i, p[i]);

  print(cur);

  int Q;
  cin >> Q;
  while (Q--) {
    double np; int u;
    cin >> u >> np;

    int g = deg[u];
    u = ord[u];

    ll pp = (ll)(np * 10000 + 0.5);
    ll diff = pp - p[u];

    ll adj_sum = s.query(vs[u] + 1, ve[u]);
    if (par[u] != -1) adj_sum += p[par[u]];

    cur += (ll)(g + 1) * diff;
    cur -= 2 * (adj_sum / 100) * (diff / 100);

    p[u] = pp;
    s.update(u, pp);

    print(cur);
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
