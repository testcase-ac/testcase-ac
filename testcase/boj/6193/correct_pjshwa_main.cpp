#include <bits/stdc++.h> 
using namespace std;

const int MAX = 1 << 21;
int tree[MAX];

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

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = 0;
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    tree[si] = max(tree[si * 2 + 1], tree[si * 2 + 2]);
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

int main() {
  fast_io();

  int n;
  cin >> n;

  vector<pair<int, int>> v;
  v.resize(n);

  for (int i = 0; i < n; i++) cin >> v[i].first, v[i].second = -i;
  sort(v.begin(), v.end());
  SegmentTree s(n);

  for (int i = 0; i < n; i++) {
    auto[av, ai] = v[i];
    int lisv = s.query(0, -ai);
    s.update(-ai, lisv + 1);
  }

  cout << s.query(0, n - 1);
}
