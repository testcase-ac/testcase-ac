#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e5;
ll tree[1 << 18], lazy[1 << 18];

vector<int> graph[MAX + 1];
int vs[MAX + 1], ve[MAX + 1];
bool vis[MAX + 1];

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
  cin >> n;
  cin >> q;

  LazySeg s(n + 1);
  while (q--) {
    int qi, ai, bi;
    cin >> qi >> ai;
    if (qi == 1) {
      cin >> bi;
      s.update(ai - 1, bi - 1, 1);
      s.update(bi, bi, ai - bi - 1);
    }
    if (qi == 2) cout << s.query(0, ai - 1) << '\n';
  }
}
