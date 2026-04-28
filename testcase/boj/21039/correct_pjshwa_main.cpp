#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class TreeNode {
public:
  int lmax0 = 1, rmax0 = 1, mmax0 = 1, all0 = 1;
  int lmax1 = 0, rmax1 = 0, mmax1 = 0, all1 = 0;
  bool def = false;

  void flip() {
    swap(lmax0, lmax1);
    swap(rmax0, rmax1);
    swap(mmax0, mmax1);
    swap(all0, all1);
  }

  void print() {
    cout << "lmax0: " << lmax0 << ", rmax0: " << rmax0 << ", mmax0: " << mmax0 << ", all0: " << all0 << '\n';
    cout << "lmax1: " << lmax1 << ", rmax1: " << rmax1 << ", mmax1: " << mmax1 << ", all1: " << all1 << '\n';
  }
};

TreeNode merge(TreeNode& lhs, TreeNode& rhs) {
  if (lhs.def) return rhs;
  if (rhs.def) return lhs;

  TreeNode ret;

  ret.lmax0 = lhs.lmax0;
  if (lhs.all0) ret.lmax0 = max(ret.lmax0, lhs.all0 + rhs.lmax0);
  ret.rmax0 = rhs.rmax0;
  if (rhs.all0) ret.rmax0 = max(ret.rmax0, rhs.all0 + lhs.rmax0);
  ret.mmax0 = max({lhs.mmax0, rhs.mmax0, lhs.rmax0 + rhs.lmax0});
  ret.all0 = lhs.all0 && rhs.all0 ? lhs.all0 + rhs.all0 : 0;

  ret.lmax1 = lhs.lmax1;
  if (lhs.all1) ret.lmax1 = max(ret.lmax1, lhs.all1 + rhs.lmax1);
  ret.rmax1 = rhs.rmax1;
  if (rhs.all1) ret.rmax1 = max(ret.rmax1, rhs.all1 + lhs.rmax1);
  ret.mmax1 = max({lhs.mmax1, rhs.mmax1, lhs.rmax1 + rhs.lmax1});
  ret.all1 = lhs.all1 && rhs.all1 ? lhs.all1 + rhs.all1 : 0;

  return ret;
}

TreeNode default_node() {
  return {0, 0, 0, 0, 0, 0, 0, 0, true};
}

const ll MAX = 5e5, INF = 1e18;

class LazySegFlip {

public:
  LazySegFlip(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    lazy.resize(2 * flag);

    __init(0, 0, n - 1);
  }

  void update(int L, int R) {
    __update_range(0, 0, n - 1, L, R);
  }

  ll query(int L, int R) {
    return max(__query(0, n - 1, L, R, 0).mmax0, __query(0, n - 1, L, R, 0).mmax1);
  }

private:
  int n, flag;
  vector<TreeNode> tree;
  vector<int> lazy;

  void __init(int si, int ss, int se) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = {1, 1, 1, 1, 0, 0, 0, 0, false};
      return;
    }

    int mid = (ss + se) / 2;
    __init(si * 2 + 1, ss, mid);
    __init(si * 2 + 2, mid + 1, se);

    tree[si] = merge(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si].flip();
      if (ss != se) {
        lazy[si * 2 + 1] ^= lazy[si];
        lazy[si * 2 + 2] ^= lazy[si];
      }
      lazy[si] = 0;
    }
  }

  void __update_range(int si, int ss, int se, int us, int ue) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] ^= 1;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __update_range(si * 2 + 1, ss, mid, us, ue);
    __update_range(si * 2 + 2, mid + 1, se, us, ue);

    tree[si] = merge(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  TreeNode __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return default_node();
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    TreeNode lhs = __query(ss, mid, qs, qe, 2 * si + 1), rhs = __query(mid + 1, se, qs, qe, 2 * si + 2);

    auto ret = merge(lhs, rhs);
    return ret;
  }
};

void solve() {
  int N, Q; string S; cin >> N >> Q >> S;

  LazySegFlip seg(N + 1);
  for (int i = 1; i <= N; ++i) {
    if (S[i - 1] == '1') seg.update(i, i);
  }

  while (Q--) {
    int c, L, R; cin >> c >> L >> R;
    if (c == 1) seg.update(L, R);
    else cout << seg.query(L, R) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
