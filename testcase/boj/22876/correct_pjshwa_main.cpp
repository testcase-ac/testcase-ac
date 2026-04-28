#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int CMAX = 1e6 + 1, SMAX = 1 << 21, NMAX = 3e5;
int N;
ll cnt_x[CMAX], cnt_y[CMAX];
pii tree_x[SMAX], tree_y[SMAX];
unordered_map<int, vector<pii>> cvalues_x, cvalues_y;

class SegmentTree {

public:
  SegmentTree(bool O) {
    n = CMAX;
    ori = O;
    __init(0, n - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  pii query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
  bool ori;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      if (ori) tree_x[si] = {cnt_x[ss], 0};
      else tree_y[si] = {cnt_y[ss], 0};
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    pii lhs, rhs;
    if (ori) lhs = tree_x[si * 2 + 1], rhs = tree_x[si * 2 + 2];
    else lhs = tree_y[si * 2 + 1], rhs = tree_y[si * 2 + 2];

    int o[4] = {lhs.first, lhs.second, rhs.first, rhs.second};
    sort(o, o + 4);

    if (ori) tree_x[si] = {o[3], o[2]};
    else tree_y[si] = {o[3], o[2]};
  }

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      if (ori) tree_x[si] = {val, 0};
      else tree_y[si] = {val, 0};
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    pii lhs, rhs;
    if (ori) lhs = tree_x[si * 2 + 1], rhs = tree_x[si * 2 + 2];
    else lhs = tree_y[si * 2 + 1], rhs = tree_y[si * 2 + 2];

    int o[4] = {lhs.first, lhs.second, rhs.first, rhs.second};
    sort(o, o + 4);

    if (ori) tree_x[si] = {o[3], o[2]};
    else tree_y[si] = {o[3], o[2]};
  }

  pii __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return {0, 0};
    if (ss >= qs && se <= qe) return ori ? tree_x[si] : tree_y[si];

    int mid = (ss + se) / 2;
    pii lhs = __query(ss, mid, qs, qe, si * 2 + 1), rhs = __query(mid + 1, se, qs, qe, si * 2 + 2);
    int o[4] = {lhs.first, lhs.second, rhs.first, rhs.second};
    sort(o, o + 4);

    return {o[3], o[2]};
  }
};

int main() {
  fast_io();

  cin >> N;
  for (int i = 0; i < N; i++) {
    int x, y, v;
    cin >> x >> y >> v;
    cnt_x[x] += v;
    cnt_y[y] += v;
    cvalues_x[x].push_back({y, v});
    cvalues_y[y].push_back({x, v});
  }

  SegmentTree sx(true), sy(false);

  ll ans = 0;

  for (auto &p : cvalues_x) {
    int x = p.first;
    auto &vec = p.second;

    for (auto [y, v] : vec) {
      int ov = sy.query(y, y).first;
      sy.update(y, ov - v);
    }

    auto [s1, s2] = sy.query(0, CMAX - 1);
    ans = max(ans, cnt_x[x] + s1 + s2);

    for (auto [y, v] : vec) {
      int ov = sy.query(y, y).first;
      sy.update(y, ov + v);
    }
  }

  for (auto &p : cvalues_y) {
    int y = p.first;
    auto &vec = p.second;

    for (auto [x, v] : vec) {
      int ov = sx.query(x, x).first;
      sx.update(x, ov - v);
    }

    auto [s1, s2] = sx.query(0, CMAX - 1);
    ans = max(ans, cnt_y[y] + s1 + s2);

    for (auto [x, v] : vec) {
      int ov = sx.query(x, x).first;
      sx.update(x, ov + v);
    }
  }

  sort(cnt_x, cnt_x + CMAX);
  sort(cnt_y, cnt_y + CMAX);
  ans = max(ans, cnt_x[CMAX - 1] + cnt_x[CMAX - 2] + cnt_x[CMAX - 3]);
  ans = max(ans, cnt_y[CMAX - 1] + cnt_y[CMAX - 2] + cnt_y[CMAX - 3]);
  cout << ans;
}
