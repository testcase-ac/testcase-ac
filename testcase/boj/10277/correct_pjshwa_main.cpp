#include <bits/stdc++.h>
using namespace std;

const int MAX = 1 << 24;
const int QSUM = 0, QMIN = 1, QMAX = 2;
const int INF = 1e9 + 7;
int tree[MAX], lazy[MAX], mmin[MAX], mmax[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
  }

  void update(int L, int R, int diff) {
    __updateRange(0, 0, n - 1, L, R, diff);
  }

  int query(int L, int R, int qtype) {
    return __query(0, n - 1, L, R, 0, qtype);
  }

private:
  int n;

  void updateLazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += (se - ss + 1) * lazy[si];
      mmin[si] += lazy[si];
      mmax[si] += lazy[si];

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }
      lazy[si] = 0;
    }
  }

  void __updateRange(int si, int ss, int se, int us, int ue, int diff) {
    updateLazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = diff;
      updateLazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __updateRange(si * 2 + 1, ss, mid, us, ue, diff);
    __updateRange(si * 2 + 2, mid + 1, se, us, ue, diff);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
    mmin[si] = min(mmin[si * 2 + 1], mmin[si * 2 + 2]);
    mmax[si] = max(mmax[si * 2 + 1], mmax[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si, int qtype) {
    updateLazy(si, ss, se);

    int base, seg;
    if (qtype == QSUM) base = 0, seg = tree[si];
    if (qtype == QMIN) base = INF, seg = mmin[si];
    if (qtype == QMAX) base = -INF, seg = mmax[si];

    if (ss > se || ss > qe || se < qs) return base;
    if (ss >= qs && se <= qe) return seg;

    int mid = (ss + se) / 2;
    int lhs = __query(ss, mid, qs, qe, 2 * si + 1, qtype);
    int rhs = __query(mid + 1, se, qs, qe, 2 * si + 2, qtype);

    if (qtype == QSUM) return lhs + rhs;
    if (qtype == QMIN) return min(lhs, rhs);
    if (qtype == QMAX) return max(lhs, rhs);
  }

};

int main() {
  fast_io();

  int n, lim, q, a, b, c;
  string qs;
  cin >> n >> lim >> q;

  LazySeg s(n);
  while (q--) {
    cin >> qs;
    if (qs == "state") {
      cin >> a;
      cout << s.query(a, a, QSUM) << '\n';
    }
    else {
      cin >> a >> b;
      if (qs == "change") c = b, b = a;
      else cin >> c;

      if (c > 0) {
        int mv = s.query(a, b, QMAX);
        c = min(c, lim - mv);
      }
      else {
        int mv = s.query(a, b, QMIN);
        c = max(c, -mv);
      }

      s.update(a, b, c);
      cout << c << '\n';
    }
  }
}
