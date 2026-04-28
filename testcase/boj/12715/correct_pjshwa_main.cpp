#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define getidx(v, x) (lower_bound(all(v), x) - v.begin())
using namespace std;
using ll = long long;

const int MAX = 5e5, MOD = 1e9 + 7;
int a[100], b[MAX], tree[1 << 20];
int tc;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]) % MOD;
  }
    
  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = (tree[si] + val) % MOD;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]) % MOD;
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return (__query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2)) % MOD;
  }

};

void solve() {
  int n, m, x, y, z;
  cin >> n >> m >> x >> y >> z;
  for (int i = 0; i < m; i++) cin >> a[i];

  vector<int> cpoints(n);
  for (int i = 0; i < n; i++) {
    b[i] = cpoints[i] = a[i % m];
    a[i % m] = ((ll)x * a[i % m] + (ll)y * (i + 1)) % z;
  }
  compress(cpoints);

  SegmentTree st(cpoints.size());
  int ans = 0;
  for (int i = 0; i < n; i++) {
    int idx = getidx(cpoints, b[i]);
    int res = (st.query(0, idx - 1) + 1) % MOD;
    ans = (ans + res) % MOD;
    st.add(idx, res);
  }

  cout << "Case #" << ++tc << ": " << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
