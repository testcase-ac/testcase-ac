#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

class TreeNode {
public:
  ll lmax, rmax, mmax, vall;
};

const int MAX = 1 << 18;
const ll INF = 1e16;
TreeNode tree[MAX];
ll k[MAX], p[MAX], tmin[MAX], tmax[MAX];

class SegmentTreeMaxSubArray {

public:
  SegmentTreeMaxSubArray(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  TreeNode query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      ll val = k[ss];
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

class SegmentTreeMin {

public:
  SegmentTreeMin(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tmin[si] = p[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tmin[si] = min(tmin[si * 2 + 1], tmin[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return INF;
    if (ss >= qs && se <= qe) return tmin[si];

    int mid = (ss + se) / 2;
    return min(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};


class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tmax[si] = p[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tmax[si] = max(tmax[si * 2 + 1], tmax[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return -INF;
    if (ss >= qs && se <= qe) return tmax[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, q;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> k[i];
  p[0] = 0;
  for (int i = 0; i < n; i++) p[i + 1] = p[i] + k[i];

  cin >> q;
  SegmentTreeMaxSubArray sa(n);
  SegmentTreeMin sm(n + 1);
  SegmentTreeMax sx(n + 1);

  while (q--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--; y1--; x2--; y2--;
    if (y1 < x2) cout << sx.query(x2 + 1, y2 + 1) - sm.query(x1, y1) << '\n';
    else {
      auto ans1 = sx.query(y1 + 2, y2 + 1) - sm.query(x1, y1);
      auto ans2 = sx.query(x2 + 1, y2 + 1) - sm.query(x1, x2 - 1);
      auto ans3 = sa.query(x2, y1).mmax;
      cout << max(ans1, max(ans2, ans3)) << '\n';
    }
  }
}
