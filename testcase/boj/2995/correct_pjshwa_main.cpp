#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5, MAXV = 1e6;
int from[MAXN], lasti[MAXV + 1];

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
  vector<pii> A;
  for (int i = 0; i < N; ++i) {
    int l, u; cin >> l >> u;
    A.push_back({l, u});
  }
  sort(A.begin(), A.end(), [](const pii &a, const pii &b) {
    auto [al, au] = a;
    auto [bl, bu] = b;
    return al != bl ? al > bl : au < bu;
  });

  SegmentTreeMax S(MAXV + 1); 
  auto find_v = [&](int u, int target) {
    int l = 0, r = u;
    while (l < r) {
      int m = (l + r) / 2;
      if (S.query(0, m) >= target) r = m;
      else l = m + 1;
    }
    return l;
  };

  int ans = 0, ansi = -1;
  memset(from, -1, sizeof from);
  memset(lasti, -1, sizeof lasti);

  for (int i = 0; i < N; ++i) {
    auto [l, u] = A[i];
    int val = S.query(l, u);
    int pu = find_v(u, val);

    S.update(u, val + 1);
    from[i] = lasti[pu];
    lasti[u] = i;

    if (val >= ans) {
      ans = val + 1;
      ansi = i;
    } 
  }

  cout << ans << '\n';
  while (ansi != -1) {
    auto [l, u] = A[ansi];
    cout << l << ' ' << u << '\n';
    ansi = from[ansi];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

