#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
#define getidx(v, x) (lower_bound(all(v), x) - v.begin())

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAXV = 1e6;

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n, flag;
  vector<ll> tree;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    int left = si * 2 + 1, right = si * 2 + 2;
    tree[si] = tree[left] + tree[right];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};

void solve() {
  int N;
  cin >> N;

  vector<tii> A(N);
  vector<int> ys;
  for (int i = 0; i < N; i++) {
    int li, ri, vi;
    cin >> li >> ri >> vi;
    A[i] = {li, ri, vi};
    ys.push_back(ri);
  }
  sort(all(A), [] (const tii& a, const tii& b) {
    auto [al, ar, av] = a;
    auto [bl, br, bv] = b;

    if (al == bl) return ar < br;
    return al > bl;
  });

  compress(ys);
  SegmentTree s(MAXV + 1);

  ll ans = 0;
  for (auto [l, r, v] : A) {
    int x = getidx(ys, r);
    ans = max(ans, s.query(0, x) + v);
    s.add(x, v);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
