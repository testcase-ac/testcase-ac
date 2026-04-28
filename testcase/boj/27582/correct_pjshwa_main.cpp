#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

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
    if (ss > se || ss > qe || se < qs) return -1;
    if (ss >= qs && se <= qe) return tmax[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};

void solve() {
  int N; cin >> N;
  SegmentTreeMax st(N);
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    st.update(i, x);
  }

  vector<vector<int>> res; int t = N;
  while (t) {
    int i = 0, v = -1;
    vector<int> cur;

    while (i < N) {
      int l = i, r = N;
      while (l < r) {
        int mid = (l + r) / 2;
        if (st.query(i, mid) > v) r = mid;
        else l = mid + 1;
      }
      int val = st.query(l, l);
      if (val == -1) break;
      cur.push_back(val);
      st.update(l, -1);
      i = l + 1; v = cur.back(); --t;
    }
    res.push_back(cur);
  }

  cout << res.size() << '\n';
  for (auto& v : res) {
    for (auto& x : v) cout << x << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
