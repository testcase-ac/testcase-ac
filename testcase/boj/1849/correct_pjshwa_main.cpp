#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e5 + 1;
int tree[1 << 18];

class SegmentTree {

public:
  SegmentTree() {
    n = MAX;
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

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

SegmentTree s;

bool do_search(int x, int ai) {
  return x - s.query(1, x) <= ai;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  vector<int> ans(n);
  for (int i = 1; i <= n; i++) {
    int ai;
    cin >> ai;

    int left = 1, right = n;
    int mid = (left + right) / 2;
    while (left < right) {
      if (do_search(mid, ai)) left = mid + 1;
      else right = mid;
      mid = (left + right) / 2;
    }
    s.inc(mid);
    ans[mid - 1] = i;
  }

  for (int e : ans) cout << e << '\n';
}
