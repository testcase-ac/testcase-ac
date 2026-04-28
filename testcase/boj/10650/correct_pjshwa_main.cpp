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

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __update(int si, int ss, int se, int p, ll val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]);
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, si * 2 + 1) + __query(mid + 1, se, qs, qe, si * 2 + 2);
  }
};

class SegmentTreeMax {

public:
  SegmentTreeMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void update(int P, ll val) {
    __update(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __update(int si, int ss, int se, int p, ll val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, si * 2 + 1), __query(mid + 1, se, qs, qe, si * 2 + 2));
  }
};

ll dist(pii x, pii y) {
  auto [x1, y1] = x; auto [x2, y2] = y;
  return abs(x1 - x2) + abs(y1 - y2);
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  vector<pii> A(N);
  for (auto& [x, y] : A) cin >> x >> y;

  SegmentTree st(N - 1);
  SegmentTreeMax sx(N - 1);
  for (int i = 0; i < N - 1; i++) {
    st.update(i, dist(A[i], A[i + 1]));

    if (i > 0) {
      sx.update(
        i,
        dist(A[i - 1], A[i]) + dist(A[i], A[i + 1]) - dist(A[i - 1], A[i + 1])
      );
    }
  }

  while (Q--) {
    string op; cin >> op;
    if (op == "Q") {
      int x, y; cin >> x >> y;
      x--, y--;

      cout << st.query(x, y - 1) - sx.query(x + 1, y - 1) << '\n';
    }
    if (op == "U") {
      int i, x, y; cin >> i >> x >> y;
      i--;

      A[i] = {x, y};
      if (i > 0) st.update(i - 1, dist(A[i - 1], A[i]));
      if (i < N - 1) st.update(i, dist(A[i], A[i + 1]));

      if (i > 1) sx.update(
        i - 1,
        dist(A[i - 2], A[i - 1]) + dist(A[i - 1], A[i]) - dist(A[i - 2], A[i])
      );
      if (i > 0 && i < N - 1) sx.update(
        i,
        dist(A[i - 1], A[i]) + dist(A[i], A[i + 1]) - dist(A[i - 1], A[i + 1])
      );
      if (i < N - 2) sx.update(
        i + 1,
        dist(A[i], A[i + 1]) + dist(A[i + 1], A[i + 2]) - dist(A[i], A[i + 2])
      );
    }

  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
