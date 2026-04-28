#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

const int MAX = 1e5;
ld tree[1 << 18], lazy[1 << 18];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class LazySeg {

public:
  LazySeg(int N) {
    n = N;
  }

  void update(int L, int R, ld diff) {
    __updateRange(0, 0, n - 1, L, R, diff);
  }

  ld query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

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
    
  void __updateRange(int si, int ss, int se, int us, int ue, ld diff) {
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
    
  ld __query(int ss, int se, int qs, int qe, int si) {
    updateLazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

int main() {
  fast_io();

  int h, q, r;
  cin >> h >> q >> r;
  LazySeg s(h + 2);

  while (q--) {
    ll a, b;
    cin >> a >> b;

    ll left = 1, right = h + 1;
    while (left < right) {
      ll mid = (left + right) / 2;
      if (mid * mid + mid >= 2 * a) right = mid;
      else left = mid + 1;
    }

    ll lev = h + 1 - left, start = a - left * (left - 1) / 2;
    s.update(start, start + lev, (ld)b / (lev + 1));
  }

  while (r--) {
    int a, b;
    cin >> a >> b;
    cout << fixed << setprecision(10) << s.query(a, b) << '\n';
  }
}
