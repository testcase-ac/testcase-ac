#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5, INF = 0x3f3f3f3f;

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

SegmentTreeMax S(MAX + 1);
vector<int> P[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) P[i].clear();

  for (int i = 1; i <= N; i++) {
    int x; cin >> x;
    S.update(i, x);
    P[x].push_back(i);
  }

  for (int i = 1; i <= N; i++) {
    if (P[i].size() < 2) continue;

    for (int j = 1; j < P[i].size(); j++) {
      int l = P[i][j - 1], r = P[i][j];
      int m = S.query(l, r);
      if (m > i) return cout << "No\n", void();
    }
  }

  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
