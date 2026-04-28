#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 2e5 + 1;
int tree[1 << 19];

class SegmentTree {

public:
  SegmentTree() {
    n = MAX;
    memset(tree, 0, sizeof(tree));
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] += val;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return max(__query(ss, mid, qs, qe, 2 * si + 1), __query(mid + 1, se, qs, qe, 2 * si + 2));
  }
};

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[MAX], dl[MAX], dr[MAX];

void solve() {
  int n;
  cin >> n;
  vector<pair<int, int>> a;
  a.resize(n);
  for (int i = 0; i < n; i++) cin >> a[i].first, a[i].second = -i;

  dl[0] = 1;
  for (int i = 1; i < n; i++) {
    if (a[i].first > a[i - 1].first) dl[i] = dl[i - 1] + 1;
    else dl[i] = 1;
  }

  dr[n - 1] = 1;
  for (int i = n - 2; i >= 0; i--) {
    if (a[i].first < a[i + 1].first) dr[i] = dr[i + 1] + 1;
    else dr[i] = 1;
  }

  sort(a.begin(), a.end());

  SegmentTree s;
  int ans = 0;
  for (int i = n - 1; i >= 0; i--) {
    int ix = -a[i].second;
    int mx = s.query(ix, n - 1);
    s.add(ix, dr[ix]);
    ans = max(ans, mx + dl[ix]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
