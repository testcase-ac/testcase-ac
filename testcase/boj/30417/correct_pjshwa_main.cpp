#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

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

const int MAX = 2e5;
int dp[MAX + 1], C[MAX + 1];
vector<pii> P[MAX + 1];

void solve() {
  int N, M; cin >> N >> M;

  int maxx = 0;
  for (int i = 0; i < M; ++i) {
    int x, r, c; cin >> x >> r >> c;
    maxx = max(maxx, x);
    C[x] = c;
    P[x + r].emplace_back(2 * r, c);
  }

  int ans = INF;
  SegmentTreeMin st(2 * N + 1);
  for (int i = 1; i <= 2 * N; ++i) {
    dp[i] = dp[i - 1] + C[i];
    for (auto& [r, c] : P[i]) {
      int val = st.query(max(0, i - r - 1), i - 1) + c;
      if (i >= maxx) ans = min(ans, val);
      dp[i] = min(dp[i], val);
    }
    st.update(i, dp[i]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
