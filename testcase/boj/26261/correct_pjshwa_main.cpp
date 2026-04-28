#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5, INF = 0x3f3f3f3f;

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

int P[MAXN + 1];

void solve() {
  int N, X, K; cin >> N >> X >> K;

  SegmentTreeMin dp(N + 1);
  for (int i = 1; i <= N; ++i) {
    cin >> P[i], P[i] += P[i - 1];
    dp.update(i, INF);
  }
  dp.update(0, 0);

  for (int i = K; i <= N - 1; ++i) {
    int sum = P[i] - P[i - K];
    if (sum > 0) continue;

    int l = max(0, i - X), r = i - K;
    int min = dp.query(l, r) + 1, cur = dp.query(i, i);
    if (min < cur) dp.update(i, min);
  }

  int ans = dp.query(N - X, N - 1) + 1;
  cout << (ans >= INF ? -1 : ans) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
