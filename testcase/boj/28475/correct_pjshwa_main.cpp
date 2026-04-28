#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN + 1];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tree;

  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    tree[si] = tree[left] + tree[right];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

bool is_orthogonal(int x, int y) {
  if ((x + 2) % 8 == y) return true;
  if ((x + 6) % 8 == y) return true;
  return false;
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  SegmentTree s(N + 1);
  for (int i = 2; i <= N; ++i) {
    s.update(i, is_orthogonal(A[i], A[i - 1]));
  }

  while (M--) {
    int op, a, b; cin >> op >> a >> b;
    if (op == 1) {
      A[a] = b;
      if (a > 1) s.update(a, is_orthogonal(A[a], A[a - 1]));
      if (a < N) s.update(a + 1, is_orthogonal(A[a + 1], A[a]));
    }
    if (op == 2) {
      int r = s.query(a + 1, b);
      cout << (r == 0) << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
