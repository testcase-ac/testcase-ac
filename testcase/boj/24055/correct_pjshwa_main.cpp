#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 5e5;
int A[MAXN], B[MAXN], N;
map<int, int> to, fro;

void print_A() {
  for (int i = 0; i < N; ++i) {
    cout << fro[A[i]] << ' ';
  }
  cout << '\n';
}

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
    tree[si] = (tree[left] + tree[right]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return (__query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2));
  }
};

void solve() {
  ll K; cin >> N >> K;

  for (int i = 0; i < N; ++i) {
    cin >> A[i];
    B[i] = A[i];
  }
  sort(B, B + N);

  for (int i = 0; i < N; ++i) {
    to[B[i]] = i;
    fro[i] = B[i];
  }
  for (int i = 0; i < N; ++i) A[i] = to[A[i]];

  SegmentTree st(N); ll acc = 0;
  for (int i = 0; i < N; ++i) {
    int qry = st.query(A[i] + 1, N - 1);
    st.update(A[i], 1);
    if (qry == 0) continue;

    int val = qry + 1;
    if (acc + val < K) {
      acc += val;
      continue;
    }

    sort(A, A + i);
    int j = i - 1, cur = A[i];
    while (j >= 0 && cur < A[j]) {
      A[j + 1] = A[j];
      --j; ++acc;
      if (acc == K) return print_A();
    }
    A[j + 1] = cur;
    return print_A();
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
