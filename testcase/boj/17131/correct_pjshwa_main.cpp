#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 4e5 + 1, MOD = 1e9 + 7, bias = 2e5;
int treel[1 << 20], treer[1 << 20];

class SegmentTreeL {

public:
  SegmentTreeL() {
    n = MAX;
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
    n = MAX;
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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> ys[MAX];

int main() {
  fast_io();

  SegmentTreeL sl;
  SegmentTreeR sr;

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    sr.inc(y + bias);
    ys[x + bias].push_back(y + bias);
  }

  ll ans = 0;
  for (int i = 0; i <= MAX; i++) {
    for (int e : ys[i]) sr.dec(e);

    for (int e : ys[i]) {
      ll l = sl.query(0, MAX - 1) - sl.query(0, e);
      ll r = sr.query(0, MAX - 1) - sr.query(0, e);
      ans = (ans + l * r) % MOD;
    }

    for (int e : ys[i]) sl.inc(e);
  }

  cout << ans << '\n';
}
