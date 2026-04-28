#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
  }

  int kth(int k) {
    // cout << "kth(" << k << ")\n";
    return __kth(0, n - 1, 1, k);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tree;

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

  int __kth(int L, int R, int i, int k) {
    if (L == R) return L;

    int mid = (L + R) / 2, qr = tree[(i << 1) - 1];
    if (qr >= k) return __kth(L, mid, i << 1, k);
    else return __kth(mid + 1, R, (i << 1) + 1, k - qr);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

const int MAXN = 1e6;
int A[MAXN], V[MAXN + 1];

void solve() {
  int N; cin >> N;

  SegmentTree s(N);
  A[0] = 1; V[1] = 0;
  for (int i = 1; i < N; ++i) s.inc(i);

  for (int i = 1; i < N; ++i) {
    int pi, xi; cin >> pi >> xi;

    int tot = N - i, num = i + 1;
    xi %= tot;
    if (xi == 0) xi = tot;

    int lsum = s.query(0, V[pi]), rsum = s.query(V[pi], N - 1), spot;
    if (rsum < xi) {
      spot = s.kth(xi - rsum);
    }
    else {
      spot = s.kth(lsum + xi);
    }
    // cout << "lsum: " << lsum << " rsum: " << rsum << " xi: " << xi << " spot: " << spot << '\n';

    s.dec(spot);
    A[spot] = num; V[num] = spot;
  }

  for (int i = 0; i < N; ++i) cout << A[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
