#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

const int MAX = 1 << 18;
int tree[MAX];
int a[MAX], d[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
  }

  void inc(int P) {
    __add(0, 0, n - 1, P, 1);
  }

  void dec(int P) {
    __add(0, 0, n - 1, P, -1);
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

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }
};


int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  unordered_map<int, int> last;
  for (int i = 0; i < n; i++) {
    if (last.count(a[i])) d[i] = last[a[i]];
    else d[i] = -1;
    last[a[i]] = i;
  }

  int q;
  cin >> q;
  vector<tii> queries(q);
  for (int i = 0; i < q; i++) {
    int l, r;
    cin >> l >> r;
    queries[i] = make_tuple(r - 1, l - 1, i);
  }
  sort(queries.begin(), queries.end());

  vector<int> ans(q);
  SegmentTree s(n);
  int qi = 0;
  for (int ri = 0; ri < n; ri++) {
    s.inc(ri);
    if (d[ri] != -1) s.dec(d[ri]);

    while (qi < q && get<0>(queries[qi]) <= ri) {
      auto [r, l, i] = queries[qi];
      ans[i] = s.query(l, r);
      qi++;
    }
  }

  for (int e : ans) cout << e << '\n';
}
