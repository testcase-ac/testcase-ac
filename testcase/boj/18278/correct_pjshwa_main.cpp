#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
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
  int n, flag;
  vector<int> tree;

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

const int MAXV = 3e5;

void solve() {
  int N, Q; string S; cin >> N >> Q >> S;
  SegmentTree Ct(MAXV + 1), Zt(MAXV + 1);
  vector<int> scores(N);

  for (int i = 0; i < N; ++i) {
    if (S[i] == 'C') Ct.inc(0);
    else Zt.inc(0);
  }

  ll cur = 0;
  for (int i = 0; i < Q; ++i) {
    int xi, di; cin >> xi >> di; --xi;
    int pre = scores[xi];
    int nxt = pre + di;
    scores[xi] = nxt;

    if (S[xi] == 'C') {
      Ct.dec(pre); Ct.inc(nxt);
      int off = Zt.query(pre, nxt - 1);
      cur += off;
    } else {
      Zt.dec(pre); Zt.inc(nxt);
      int off = Ct.query(pre + 1, nxt);
      cur -= off;
    }

    cout << cur << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
