#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

struct Func {
  int f[5];

  static Func identity() {
    return Func(0, 1, 2, 3, 4);
  }

  Func(int f1, int f2, int f3, int f4, int f5) {
    f[0] = f1; f[1] = f2; f[2] = f3; f[3] = f4; f[4] = f5;
  }

  Func() {
    f[0] = 0; f[1] = 1; f[2] = 2; f[3] = 3; f[4] = 4;
  }

  // Composition
  Func operator* (const Func& rhs) const {
    return Func(f[rhs.f[0]], f[rhs.f[1]], f[rhs.f[2]], f[rhs.f[3]], f[rhs.f[4]]);
  }

  Func inverse() const {
    Func ret;
    for (int i = 0; i < 5; i++) {
      ret.f[f[i]] = i;
    }
    return ret;
  }
};

template <class T>
class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void update(int P, T val) {
    __update(0, 0, n - 1, P, val);
  }

  T query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<T> tree;

  void __update(int si, int ss, int se, int p, T val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    tree[si] = tree[left] * tree[right];
  }

  T __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return T::identity();
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) * __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

void solve() {
  int N; cin >> N;

  Func id = Func(0, 1, 2, 3, 4);
  SegmentTree<Func> s(N);
  for (int i = 0; i < N; i++) {
    int f1, f2, f3, f4, f5; cin >> f1 >> f2 >> f3 >> f4 >> f5;
    s.update(i, Func(f1 - 1, f2 - 1, f3 - 1, f4 - 1, f5 - 1));
  }

  int Q; cin >> Q;
  while (Q--) {
    int u, a, b, r[5];
    cin >> u >> a >> b >> r[0] >> r[1] >> r[2] >> r[3] >> r[4];

    Func o = Func(r[0] - 1, r[1] - 1, r[2] - 1, r[3] - 1, r[4] - 1);

    // o = pre * R * post
    // Solve for R
    auto pre = s.query(a - 1, u - 2);
    auto post = s.query(u, b - 1);
    auto R = pre.inverse() * o * post.inverse();

    s.update(u - 1, R);
    for (int i = 0; i < 5; i++) {
      cout << R.f[i] + 1 << " \n"[i == 4];
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
