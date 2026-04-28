#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 3e5;
ll A[MAXN];

class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmax.resize(2 * flag);
  }

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tmax;

  void __update(int si, int ss, int se, int p, ll val) {
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

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tmax[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};

void solve() {
  int N; cin >> N;

  set<ll> U;
  for (int i = 0; i < N; ++i) cin >> A[i], U.insert(A[i]);

  int it = 0; map<ll, int> W;
  for (ll e : U) W[e] = it++;

  SegmentTreeMax S(it);
  for (int i = 0; i < N; ++i) {
    int j = W[A[i]];
    ll pre = S.query(0, j - 1);
    S.update(j, pre + A[i]);
  }
  cout << S.query(0, it - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
