#include <bits/stdc++.h>
#define pii pair<int, int>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXN = 1000, MAXP = 5e5;
int treel[1 << 20], treer[1 << 20];

class SegmentTreeL {

public:
  SegmentTreeL() {
    n = MAXP;
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      treel[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    treel[si] = treel[si * 2 + 1] + treel[si * 2 + 2];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return treel[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

class SegmentTreeR {

public:
  SegmentTreeR() {
    n = MAXP;
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      treer[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    treer[si] = treer[si * 2 + 1] + treer[si * 2 + 2];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return treer[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

int lw, rw;
SegmentTreeL sl;
SegmentTreeR sr;

int mmax(int yi) {
  int lu = sl.query(0, yi);
  int ru = sr.query(0, yi);
  return -max({lu, ru, lw - lu, rw - ru});
}

int main() {
  fast_io();

  int n;
  cin >> n;
  map<int, vector<int>> xs;
  vector<int> ys;

  for (int i = 0; i < n; i++) {
    int xi, yi;
    cin >> xi >> yi;
    xi = (xi + 1) / 2;
    yi = (yi + 1) / 2;

    xs[xi].push_back(yi);
    ys.push_back(yi);
    sr.inc(yi);
  }
  compress(ys);

  lw = 0, rw = n;
  int ans = 1e9;
  for (auto [xi, yv] : xs) {
    for (int yi : yv) {
      lw++;
      rw--;
      sl.inc(yi);
      sr.dec(yi);
    }

    int left = 0, right = MAXP;
    while (right - left >= 3) {
      int mid1 = left + (right - left) / 3;
      int mid2 = right - (right - left) / 3;
      if (mmax(mid1) < mmax(mid2)) left = mid1;
      else right = mid2;
    }
    for (int i = left; i <= right; i++) ans = min(ans, -mmax(i));
  }

  cout << ans << '\n';
}
