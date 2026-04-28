#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e7, INF = 0x3f3f3f3f;
set<int> inv[MAX + 1];

class SegmentTreeMin {

public:
  SegmentTreeMin(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmin.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tmin;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmin[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tmin[si] = min(tmin[si * 2 + 1], tmin[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return INF;
    if (ss >= qs && se <= qe) return tmin[si];

    int mid = (ss + se) / 2;
    return min(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};


class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmax.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tmax;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tmax[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return -INF;
    if (ss >= qs && se <= qe) return tmax[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};

void solve() {
  int N;
  cin >> N;

  vector<int> A(N);
  vector<SegmentTreeMax> smax_f(25, SegmentTreeMax(N));
  vector<SegmentTreeMax> smax_b(25, SegmentTreeMax(N));

  for (int i = 0; i < N; i++) {
    cin >> A[i];

    int pf = 0, pb = 0;
    for (int b = 24; b >= 0; b--) {
      if (A[i] & (1 << b)) pf += (1 << b);
      else pb += (1 << b);

      smax_f[b].update(i, pf);
      smax_b[b].update(i, pb);
    }

    inv[A[i]].insert(i);
  }

  int Q;
  cin >> Q;
  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      l--; r--;

      int tt = 0, tb = 0;
      for (int b = 24; b >= 0; b--) {
        if (x & (1 << b)) {
          // If anything is 1, then it is 1.
          if (smax_f[b].query(l, r) == tt + (1 << b)) tt += (1 << b);
          else tb += (1 << b);
        }
        else {
          // If anything is 0, then it is 0.
          if (smax_b[b].query(l, r) == tb + (1 << b)) tb += (1 << b);
          else tt += (1 << b);
        }
      }

      cout << *inv[tt].lower_bound(l) + 1 << '\n';
    }

    if (op == 2) {
      int l, r, x;
      cin >> l >> r >> x;
      l--; r--;

      int tt = 0, tb = 0;
      for (int b = 24; b >= 0; b--) {
        if (x & (1 << b)) {
          // If anything is 0, then it is 0.
          if (smax_b[b].query(l, r) == tb + (1 << b)) tb += (1 << b);
          else tt += (1 << b);
        }
        else {
          // If anything is 1, then it is 1.
          if (smax_f[b].query(l, r) == tt + (1 << b)) tt += (1 << b);
          else tb += (1 << b);
        }
      }

      cout << *inv[tt].lower_bound(l) + 1 << '\n';
    }

    if (op == 3) {
      int p, x;
      cin >> p >> x;
      p--;

      inv[A[p]].erase(p);

      int pf = 0, pb = 0;
      for (int b = 24; b >= 0; b--) {
        if (x & (1 << b)) pf += (1 << b);
        else pb += (1 << b);

        smax_f[b].update(p, pf);
        smax_b[b].update(p, pb);
      }

      A[p] = x;
      inv[x].insert(p);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
