#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 0x3f3f3f3f;
int A[MAX + 1];

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

void solve() {
  int N, Q;
  cin >> N >> Q;

  SegmentTree s(N + 10);
  for (int i = 1; i <= N; i++) {
    cin >> A[i];
    if (A[i] < A[i - 1]) s.update(i, 1);
  }
  s.update(N + 1, INF);

  while (Q--) {
    int op, L, R;
    cin >> op >> L >> R;
    if (op == 1) {
      if (s.query(L + 1, R) == 0) cout << "CS204\n";
      else cout << "HSS090\n";
    }
    if (op == 2) {
      swap(A[L], A[R]);

      if (A[L] < A[L - 1]) s.update(L, 1);
      else s.update(L, 0);

      if (A[L + 1] < A[L]) s.update(L + 1, 1);
      else s.update(L + 1, 0);

      if (A[R] < A[R - 1]) s.update(R, 1);
      else s.update(R, 0);

      if (A[R + 1] < A[R]) s.update(R + 1, 1);
      else s.update(R + 1, 0);
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
