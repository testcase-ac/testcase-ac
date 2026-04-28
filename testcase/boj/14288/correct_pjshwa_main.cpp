#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e5, TSIZE = 1 << 18;
vector<int> graph[MAX + 1];
int vs[MAX + 1], ve[MAX + 1];
bool vis[MAX + 1];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tick = -1;
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
    tree.resize(TSIZE);
    lazy.resize(TSIZE);
    __init(0, n - 1, 0);
  }

  void update(int L, int R, ll diff) {
    __updateRange(0, 0, n - 1, L, R, diff);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
  vector<ll> tree, lazy;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) { 
      tree[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  void updateLazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += (se - ss + 1) * lazy[si];

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }
      lazy[si] = 0;
    }
  }
    
  void __updateRange(int si, int ss, int se, int us, int ue, ll diff) {
    updateLazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      tree[si] += diff * (se - ss + 1);

      if (ss != se) { 
        lazy[si * 2 + 1] += diff;
        lazy[si * 2 + 2] += diff;
      }
      return;
    }

    int mid = (ss + se) / 2;
    __updateRange(si * 2 + 1, ss, mid, us, ue, diff);
    __updateRange(si * 2 + 2, mid + 1, se, us, ue, diff);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }
    
  ll __query(int ss, int se, int qs, int qe, int si) {
    updateLazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    int y;
    cin >> y;
    if (y == -1) continue;

    graph[y].push_back(i);
  }
  dfs(1);

  LazySeg s1(n), s2(n);
  bool flip = false;

  while (q--) {
    int qi, a, b;
    cin >> qi;

    if (qi == 1) {
      cin >> a >> b;
      if (flip) s2.update(vs[a], vs[a], b);
      else s1.update(vs[a], ve[a], b);
    }
    if (qi == 2) cin >> a, cout << s1.query(vs[a], vs[a]) + s2.query(vs[a], ve[a]) << '\n';
    if (qi == 3) flip = !flip;
  }
}
