#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
ll tree[1 << 20], trem[1 << 20], trup[1 << 20], tcnt[1 << 20];
int tc;

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
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
    
  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

class SegmentTreeRem {

public:
  SegmentTreeRem(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      trem[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    trem[si] = trem[si * 2 + 1] + trem[si * 2 + 2];
  }
    
  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      trem[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    trem[si] = trem[si * 2 + 1] + trem[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return trem[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};


class SegmentTreeRup {

public:
  SegmentTreeRup(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      trup[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    trup[si] = trup[si * 2 + 1] + trup[si * 2 + 2];
  }
    
  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      trup[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    trup[si] = trup[si * 2 + 1] + trup[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return trup[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

class SegmentTreeCnt {

public:
  SegmentTreeCnt(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tcnt[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tcnt[si] = tcnt[si * 2 + 1] + tcnt[si * 2 + 2];
  }
    
  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tcnt[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tcnt[si] = tcnt[si * 2 + 1] + tcnt[si * 2 + 2];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tcnt[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

void solve() {
  cout << "Case #" << ++tc << ": ";

  int n, q, p;
  cin >> n >> q >> p;

  SegmentTree sv(n);
  SegmentTreeRem sr(n);
  SegmentTreeRup su(n);
  SegmentTreeCnt sc(n);
  for (int i = 0; i < n; i++) {
    ll x, ox, b, deg;
    cin >> x;
    ox = x, b = x % p;

    if (b) {
      sv.update(i, 0);
      x -= b;
      if (x) {
        deg = 0;
        while (x % p == 0) {
          deg++;
          x /= p;
        }
        sr.update(i, deg);
        sc.update(i, 1);

        x = ox + b;
        deg = 0;
        while (x % p == 0) {
          deg++;
          x /= p;
        }
        su.update(i, deg - 1);
      }
      else {
        sr.update(i, 0); su.update(i, 0); sc.update(i, 0);
      }
    }
    else {
      sr.update(i, 0); su.update(i, 0); sc.update(i, 0);
      int deg = 0;
      while (x % p == 0) {
        deg++;
        x /= p;
      }
      sv.update(i, deg);
    }
  }

  while (q--) {
    int op;
    cin >> op;
    if (op == 1) {
      ll pos, x, ox, b, i, deg;
      cin >> pos >> x;
      
      i = pos - 1;
      ox = x, b = x % p;

      if (b) {
        sv.update(i, 0);
        x -= b;
        if (x) {
          deg = 0;
          while (x % p == 0) {
            deg++;
            x /= p;
          }
          sr.update(i, deg);
          sc.update(i, 1);

          x = ox + b;
          deg = 0;
          while (x % p == 0) {
            deg++;
            x /= p;
          }
          su.update(i, deg - 1);
        }
        else {
          sr.update(i, 0); su.update(i, 0); sc.update(i, 0);
        }
      }
      else {
        sr.update(i, 0); su.update(i, 0); sc.update(i, 0);
        int deg = 0;
        while (x % p == 0) {
          deg++;
          x /= p;
        }
        sv.update(i, deg);
      }
    }
    if (op == 2) {
      ll s, l, r;
      cin >> s >> l >> r;

      ll res = s * sv.query(l - 1, r - 1) + sr.query(l - 1, r - 1);
      if (p == 2 && s % 2 == 0) res += su.query(l - 1, r - 1);
      ll cnt = sc.query(l - 1, r - 1);
      int deg = 0;
      while (s % p == 0) {
        res += cnt;
        s /= p;
      }
      cout << res << ' ';
    }
  }

  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
