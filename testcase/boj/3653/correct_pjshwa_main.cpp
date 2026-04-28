#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 2e5 + 1;
int tree[1 << 19], cpos[MAX];

class SegmentTree {

public:
  SegmentTree() {
    n = MAX;
    memset(tree, 0, sizeof(tree));
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

void solve() {
  int n, m;
  cin >> n >> m;

  SegmentTree s;
  for (int i = 1; i <= n; i++) {
    s.inc(i);
    cpos[i] = n + 1 - i;
  }

  int x;
  for (int i = 1; i <= m; i++) {
    cin >> x;
    s.dec(cpos[x]);
    cout << s.query(cpos[x] + 1, MAX - 1) << ' ';
    cpos[x] = n + i;
    s.inc(cpos[x]);
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
