#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1 << 21;
int tl[MAX], tr[MAX];

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

  ll query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
  int tree[1 << 19];

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

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
    
  void __update(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = tree[si * 2 + 1] + tree[si * 2 + 2];
  }

  ll __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2);
  }

};

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    int y;
    cin >> y;
    if (y == -1) continue;

    graph[y].push_back(i + 1);
  }
  dfs(1);

  SegmentTree s(n + 1);
  while (q--) {
    int qi, a, b;
    cin >> qi >> a;
    if (qi == 1) cin >> b, s.add(vs[a], b);
    if (qi == 2) cout << s.query(vs[a], ve[a]) << '\n';
  }
}
