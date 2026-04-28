#include <bits/stdc++.h> 
typedef long long ll;
using namespace std;

const int MAX = 3e5;
int a[MAX];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
  ll tree[MAX];

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = abs(a[ss] - a[ss + 1]);
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = gcd(tree[si * 2 + 1], tree[si * 2 + 2]);
  }
    
  void __update(int si, int ss, int se, int p, ll val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = gcd(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return gcd(__query(ss, mid, qs, qe, 2 * si + 1), __query(mid + 1, se, qs, qe, 2 * si + 2));
  }

};


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
  ll tree[MAX], lazy[MAX];

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) { 
      tree[si] = a[ss];
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
  
void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  LazySeg ls(n);
  SegmentTree s(n - 1);

  cin >> q;
  while (q--) {
    int t, ai, bi;
    cin >> t >> ai >> bi;
    ai--;
    bi--;
    if (t == 0) cout << gcd(ls.query(ai, ai), s.query(ai, bi - 1)) << '\n';
    else {
      ls.update(ai, bi, t);
      if (ai > 0) s.update(ai - 1, abs(ls.query(ai - 1, ai - 1) - ls.query(ai, ai)));
      s.update(bi, abs(ls.query(bi, bi) - ls.query(bi + 1, bi + 1)));
    }
  }

}
