#include <bits/stdc++.h> 
using namespace std;

const int MAX = 3e5;

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, int val) {
    __update(0, 0, n - 1, P, val);
  }

  int query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;
  int tree[MAX];

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = 1;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

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

int main() {
  fast_io();

  int n, ai;
  cin >> n;
  vector<pair<int, int>> a;
  a.push_back({-1, -1}); // dummy

  for (int i = 1; i <= n; i++) {
    cin >> ai;
    a.push_back(make_pair(ai, i));
  }
  sort(a.begin(), a.end());

  SegmentTree s(n);

  for (int i = 1; i <= n; i++) {
    int target, idx, res;
    if (i & 1) {
      target = i / 2 + 1;
      idx = a[target].second;
      s.update(idx - 1, 0);
      res = s.query(0, idx - 1);
    }
    else {
      target = n + 1 - i / 2;
      idx = a[target].second;
      s.update(idx - 1, 0);
      res = s.query(idx - 1, n - 1);
    }
    cout << res << '\n';
  }

}
