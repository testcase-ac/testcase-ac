#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int CMAX = 1e5 + 1, SMAX = 1 << 18;
int a[CMAX];
pii tree[SMAX];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
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

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = {a[ss], 0};
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    pii lhs, rhs;
    lhs = tree[si * 2 + 1], rhs = tree[si * 2 + 2];

    int o[4] = {lhs.first, lhs.second, rhs.first, rhs.second};
    sort(o, o + 4);

    tree[si] = {o[3], o[2]};
  }

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = {val, 0};
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    pii lhs, rhs;
    lhs = tree[si * 2 + 1], rhs = tree[si * 2 + 2];

    int o[4] = {lhs.first, lhs.second, rhs.first, rhs.second};
    sort(o, o + 4);

    tree[si] = {o[3], o[2]};
  }

  pii __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return {0, 0};
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    pii lhs = __query(ss, mid, qs, qe, si * 2 + 1), rhs = __query(mid + 1, se, qs, qe, si * 2 + 2);
    int o[4] = {lhs.first, lhs.second, rhs.first, rhs.second};
    sort(o, o + 4);

    return {o[3], o[2]};
  }
};

int main() {
  fast_io();

  int n, q;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  SegmentTree s(n);
  cin >> q;
  while (q--) {
    int t, x, y;
    cin >> t >> x >> y;
    if (t == 1) s.update(x - 1, y);
    else {
      pii ans = s.query(x - 1, y - 1);
      cout << ans.first + ans.second << '\n';
    }
  }

}
