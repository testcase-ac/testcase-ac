#include <bits/stdc++.h> 
using namespace std;

const int MAX = 1 << 18;
int tree[MAX];

class SegmentTree {

public:
  SegmentTree() {
    n = MAX >> 1;
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

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

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[MAX];

int main() {
  fast_io();

  SegmentTree s;

  int n, q;
  cin >> n >> q;
  for (int i = 0; i < n; i++) cin >> a[i];
  for (int i = 1; i < n; i++) {
    if (a[i] != a[i - 1]) s.inc(i);
  }

  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) cout << s.query(x, y - 1) + 1 << '\n';
    if (t == 2) {
      x--;
      if (x > 0) {
        if (a[x - 1] != a[x] && a[x - 1] == y) s.dec(x);
        if (a[x - 1] == a[x] && a[x - 1] != y) s.inc(x);
      }
      if (x < n - 1) {
        if (a[x + 1] != a[x] && a[x + 1] == y) s.dec(x + 1);
        if (a[x + 1] == a[x] && a[x + 1] != y) s.inc(x + 1);
      }
      a[x] = y;
    }
  }
}
