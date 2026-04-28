#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

int tree[1 << 21];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
    
  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    tree[si] = tree[left] + tree[right];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

int main() {
  fast_io();

  int n;
  vector<pair<int, int>> v;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    v.push_back({x, i});
  }
  sort(v.begin(), v.end());

  SegmentTree s(n);
  ll ans = 0;
  for (auto [x, i] : v) {
    ans += s.query(i, n - 1);
    s.inc(i);
  }
  cout << ans << '\n';
}
