#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

const int MAX = 1e5, TSIZE = 1 << 18;
int tree[TSIZE];

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

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  SegmentTree s(MAX);

  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;

    memset(tree, 0, sizeof(tree));

    ll ans = 0;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      ans += s.query(x, MAX);
      s.inc(x - 1);
    }

    cout << ans << '\n';
  }
}
