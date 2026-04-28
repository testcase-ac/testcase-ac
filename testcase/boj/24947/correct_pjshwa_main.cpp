#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

const int INF = 0x3f3f3f3f;

class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tmax.resize(2 * flag, -INF);
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
  int N; cin >> N;

  vector<tii> A; vector<int> ys, zs;
  for (int i = 0; i < N; i++) {
    int x, y, z; cin >> x >> y >> z;
    A.emplace_back(x, y, z);
    ys.push_back(y); zs.push_back(z);
  }
  sort(A.begin(), A.end());
  compress(ys); compress(zs);

  SegmentTreeMax st1(ys.size()), st2(zs.size());
  int ymax_u1 = -INF, zmax_u1 = -INF, ymax_u2 = -INF, zmax_u2 = -INF;

  auto update = [&](int ycur, int zcur) {
    int yidx = lower_bound(ys.begin(), ys.end(), ycur) - ys.begin();
    int zidx = lower_bound(zs.begin(), zs.end(), zcur) - zs.begin();

    int yqry = st1.query(0, yidx - 1), zqry = st2.query(0, zidx - 1);
    if (yqry > zcur && ycur + yqry >= ymax_u1 + zmax_u1) ymax_u1 = ycur, zmax_u1 = yqry;
    if (zqry > ycur && zcur + zqry >= ymax_u2 + zmax_u2) ymax_u2 = zqry, zmax_u2 = zcur;

    if (st1.query(yidx, yidx) < zcur) st1.update(yidx, zcur);
    if (st2.query(zidx, zidx) < ycur) st2.update(zidx, ycur);
  };

  queue<tii> q; int ans = -1;
  for (int i = 0; i < N; i++) {
    auto [xi, yi, zi] = A[i];
    while (!q.empty() && get<0>(q.front()) < xi) {
      auto [xj, yj, zj] = q.front(); q.pop();
      update(yj, zj);
    }

    if (ymax_u1 > yi && zmax_u1 > zi) ans = max(ans, xi + ymax_u1 + zmax_u1);
    if (ymax_u2 > yi && zmax_u2 > zi) ans = max(ans, xi + ymax_u2 + zmax_u2);

    q.emplace(xi, yi, zi);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
