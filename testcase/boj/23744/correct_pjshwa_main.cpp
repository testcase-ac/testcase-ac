#include <bits/stdc++.h>
using namespace std;

const int MAX = 1 << 19, INF = 1e9 + 7;
int l[MAX], r[MAX], p[MAX], tmin[MAX], tmax[MAX];
vector<int> on[MAX], off[MAX];

class SegmentTreeMin {

public:
  SegmentTreeMin(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tmin[si] = INF;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tmin[si] = min(tmin[si * 2 + 1], tmin[si * 2 + 2]);
  }

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
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tmax[si] = -INF;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

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

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> p[i] >> l[i] >> r[i];

  SegmentTreeMin sm(n + 1);
  SegmentTreeMax sx(n + 1);

  for (int i = 1; i <= n; i++) {
    if (i - r[i] <= 0) sm.update(i, p[i]), sx.update(i, p[i]);
    else on[i - r[i]].push_back(i);
    if (i - l[i] <= 0) sm.update(i, INF), sx.update(i, -INF);
    else off[i - l[i]].push_back(i);

    if (i + l[i] <= n) on[i + l[i]].push_back(i);
    if (i + r[i] <= n) off[i + r[i]].push_back(i);
  }

  int mdiff = -1;
  for (int i = 1; i <= n; i++) {
    for (int j : on[i]) sm.update(j, p[j]), sx.update(j, p[j]);

    int qm = min(sm.query(i - r[i], i - l[i]), sm.query(i + l[i], i + r[i]));
    int qx = max(sx.query(i - r[i], i - l[i]), sx.query(i + l[i], i + r[i]));
    if (qm != INF) mdiff = max(mdiff, abs(p[i] - qm));
    if (qx != -INF) mdiff = max(mdiff, abs(p[i] - qx));

    for (int j : off[i]) sm.update(j, INF), sx.update(j, -INF);
  }

  cout << mdiff << '\n';
}
