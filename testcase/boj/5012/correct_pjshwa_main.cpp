#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1 << 18;

class SegmentTree {

public:
  SegmentTree() {
    n = 1e5 + 1;
    memset(tree, 0, sizeof(tree));
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, tree[MAX];

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

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[100'000];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  SegmentTree s1, s2;
  s1.inc(a[0]);
  for (int i = 1; i < n; i++) s2.inc(a[i]);

  ll cnt = 0;
  for (int i = 1; i < n - 1; i++) {
    s2.dec(a[i]);
    cnt += s1.query(a[i] + 1, 1e5) * s2.query(1, a[i] - 1);
    s1.inc(a[i]);
  }
  cout << cnt;
}
