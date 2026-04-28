#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e5;
vector<int> graph[MAX + 1];
int vs[MAX + 1], ve[MAX + 1];
bool vis[MAX + 1];
ll tree[1 << 18], lazy[1 << 18];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tick = 0;
void dfs(int v) {
  vis[v] = true;
  vs[v] = ++tick;
  for (int d : graph[v]) {
    if (!vis[d]) dfs(d);
  }
  ve[v] = tick;
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
  }

  void assign(int L, int R, ll val) {
    __assign_range(0, 0, n - 1, L, R, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] = (se - ss + 1) * lazy[si];

      if (ss != se) {
        lazy[si * 2 + 1] = lazy[si];
        lazy[si * 2 + 2] = lazy[si];
      }
      lazy[si] = 0;
    }
  }

  void __assign_range(int si, int ss, int se, int us, int ue, ll val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = val;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __assign_range(si * 2 + 1, ss, mid, us, ue, val);
    __assign_range(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    int y;
    cin >> y;
    if (y == 0) continue;

    graph[y].push_back(i);
  }
  dfs(1);

  LazySeg s(n + 1);
  s.assign(1, n, 2);

  int q;
  cin >> q;
  while (q--) {
    int qi, a;
    cin >> qi >> a;
    if (qi == 1) s.assign(vs[a] + 1, ve[a], 2);
    if (qi == 2) s.assign(vs[a] + 1, ve[a], 1);
    if (qi == 3) cout << s.query(vs[a] + 1, ve[a]) - (ve[a] - vs[a]) << '\n';
  }
}
