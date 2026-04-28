#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, si * 2 + 1) + __query(mid + 1, se, qs, qe, si * 2 + 2);
  }
};

const int MAX = 1e5;
vector<int> graph[MAX + 1];
ll res[MAX + 1], r[MAX + 1], a[MAX + 1];
SegmentTree s(MAX + 1);

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void dfs(int v, int p) {
  ll prev = s.query(1, r[v] - 1);
  for (int u : graph[v]) {
    if (u == p) continue;
    dfs(u, v);
  }
  res[v] = s.query(1, r[v] - 1) - prev;
  s.add(r[v], a[v]);
}

void solve() {
  int n;
  cin >> n;

  int p;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x >> r[i] >> a[i];

    if (x == -1) p = i;
    else graph[x].push_back(i);
  }

  dfs(p, -1);
  for (int i = 1; i <= n; i++) cout << res[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
