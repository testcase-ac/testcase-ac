#include <bits/stdc++.h>
using namespace std;

class TreeNode {
public:
  int lmax, rmax, mmax, vall;
};

const int MAX = 1 << 18, INF = 1e9 + 7;
TreeNode tree[MAX];
int k[MAX];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  TreeNode query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      int val = k[ss];
      tree[si] = {val, val, val, val};
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    TreeNode l = tree[si * 2 + 1], r = tree[si * 2 + 2];
    tree[si].lmax = max(l.lmax, l.vall + r.lmax);
    tree[si].rmax = max(r.rmax, r.vall + l.rmax);
    tree[si].mmax = max({l.mmax, r.mmax, l.rmax + r.lmax});
    tree[si].vall = l.vall + r.vall;
  }

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = {val, val, val, val};
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    TreeNode l = tree[si * 2 + 1], r = tree[si * 2 + 2];
    tree[si].lmax = max(l.lmax, l.vall + r.lmax);
    tree[si].rmax = max(r.rmax, r.vall + l.rmax);
    tree[si].mmax = max({l.mmax, r.mmax, l.rmax + r.lmax});
    tree[si].vall = l.vall + r.vall;
  }

  TreeNode __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return {-INF, -INF, -INF, 0};
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    TreeNode l = __query(ss, mid, qs, qe, si * 2 + 1), r = __query(mid + 1, se, qs, qe, si * 2 + 2), ans;
    ans.lmax = max(l.lmax, l.vall + r.lmax);
    ans.rmax = max(r.rmax, r.vall + l.rmax);
    ans.mmax = max({l.mmax, r.mmax, l.rmax + r.lmax});
    ans.vall = l.vall + r.vall;
    return ans;
  }

};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q, u, v;
  cin >> n >> q >> u >> v;
  for (int i = 0; i < n; i++) cin >> k[i], k[i] = u * k[i] + v;
  SegmentTree s(n);

  while (q--) {
    int c, a, b;
    cin >> c >> a >> b;

    if (c == 0) cout << s.query(a - 1, b - 1).mmax - v << '\n';
    if (c == 1) s.update(a - 1, u * b + v);
  }
}
