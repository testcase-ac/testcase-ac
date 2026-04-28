#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 2e9 + 1;

class LazySegMax {

public:
  LazySegMax(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    lazy.resize(2 * flag);
  }

  void update(int L, int R, int val) {
    __update_range(0, 0, n - 1, L, R, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<int> tree, lazy;

  void __update_lazy(int si, int ss, int se) {
    if (lazy[si] != 0) {
      tree[si] += lazy[si];

      if (ss != se) {
        lazy[si * 2 + 1] += lazy[si];
        lazy[si * 2 + 2] += lazy[si];
      }
      lazy[si] = 0;
    }
  }

  void __update_range(int si, int ss, int se, int us, int ue, int val) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > ue || se < us) return;

    if (ss >= us && se <= ue) {
      lazy[si] = val;
      __update_lazy(si, ss, se);
      return;
    }

    int mid = (ss + se) / 2;
    __update_range(si * 2 + 1, ss, mid, us, ue, val);
    __update_range(si * 2 + 2, mid + 1, se, us, ue, val);

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    __update_lazy(si, ss, se);

    if (ss > se || ss > qe || se < qs) return -INF;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, 2 * si + 1), __query(mid + 1, se, qs, qe, 2 * si + 2));
  }
};

void solve() {
  int N, K; cin >> N >> K;
  
  LazySegMax seg(N); int A[N];
  for (ll i = 0; i < N; i++) {
    cin >> A[i];
    seg.update(i, i, -A[i] - i * K);
  }

  int ans = -INF;
  for (int i = 0; i < N; i++) {
    int val = max(seg.query(0, i - 1), seg.query(i + 1, N - 1));
    ans = max(ans, val + A[i]);

    seg.update(0, i, -K);
    seg.update(i + 1, N - 1, K);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
