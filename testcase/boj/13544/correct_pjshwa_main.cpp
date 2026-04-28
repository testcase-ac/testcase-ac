#include <bits/stdc++.h>
using namespace std;

const int MAX = 1 << 19;
int a[MAX / 2];
vector<int> tree[MAX];

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

class MergeSortTree {

public:
  MergeSortTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  int query(int L, int R, int val) {
    return __query(0, n - 1, L, R, 0, val);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = {a[ss]};
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    vector<int> &lhs = tree[si * 2 + 1], &rhs = tree[si * 2 + 2];
    tree[si].resize(lhs.size() + rhs.size());
    int i = 0, j = 0;
    for (int k = 0; k < lhs.size() + rhs.size(); k++) {
      if (i == lhs.size() || (j < rhs.size() && lhs[i] > rhs[j])) tree[si][k] = rhs[j++];
      else tree[si][k] = lhs[i++]; 
    }
  }

  int __query(int ss, int se, int qs, int qe, int si, int val) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si].end() - upper_bound(tree[si].begin(), tree[si].end(), val);

    int mid = (ss + se) / 2;
    return __query(ss, mid, qs, qe, 2 * si + 1, val) + __query(mid + 1, se, qs, qe, 2 * si + 2, val);
  }
};


int main() {
  fast_io();

  int N, M;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];
  cin >> M;

  MergeSortTree mt(N);
  int last_ans = 0;
  while (M--) {
    int a, b, c;
    cin >> a >> b >> c;
    a ^= last_ans, b ^= last_ans, c ^= last_ans;
    last_ans = mt.query(a - 1, b - 1, c);
    cout << last_ans << '\n';
  }
}
