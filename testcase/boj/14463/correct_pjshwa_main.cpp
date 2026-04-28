#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
int V[MAXN + 1];

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
  int N, x; cin >> N;
  memset(V, -1, sizeof V);

  vector<pii> B;
  for (int i = 0; i < 2 * N; ++i) {
    cin >> x;
    if (V[x] == -1) V[x] = i;
    else B.emplace_back(V[x], i);
  }
  sort(B.begin(), B.end());

  SegmentTree st(2 * N); ll ans = 0;
  for (auto& [s, e] : B) {
    ans += st.query(s, e);
    st.update(e, 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
