#include <bits/stdc++.h> 
using namespace std;

const int INF = 1e9 + 7;

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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k, d;
  cin >> n >> k >> d;

  int vmax = 5e5;
  SegmentTreeMax smod(vmax + 1), sdiff(vmax + 1);

  int ans = 0;
  for (int i = 0, x; i < n; i++) {
    cin >> x;

    int pmax = max(smod.query(x % k, x % k), sdiff.query(x - d, x + d)) + 1;
    ans = max(ans, pmax);

    if (smod.query(x % k, x % k) < pmax) smod.update(x % k, pmax);
    if (sdiff.query(x, x) < pmax) sdiff.update(x, pmax);
  }

  cout << ans << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
