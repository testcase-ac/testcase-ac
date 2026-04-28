#include <bits/stdc++.h>
typedef long long ll;
#define otype pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5, MOD = 1e9 + 7;
otype a[MAX];
otype tree[1 << 20];

class SegmentTree {

public:
  SegmentTree(int N) {
    n = N;
    __init(0, N - 1, 0);
  }

  void update(int P, otype val) {
    __update(0, 0, n - 1, P, val);
  }

  otype query(int L, int R) {
    return __query(0, n - 1, L, R, 0);
  }

private:
  int n;

  void __init(int ss, int se, int si) {
    if (ss > se) return;

    if (ss == se) {
      tree[si] = a[ss];
      return;
    }

    int mid = (ss + se) / 2;
    __init(ss, mid, si * 2 + 1);
    __init(mid + 1, se, si * 2 + 2);

    otype lhs = tree[si * 2 + 1], rhs = tree[si * 2 + 2];
    tree[si] = {(lhs.first * rhs.second + rhs.first) % MOD, (lhs.second * rhs.second) % MOD};
  }

  void __update(int si, int ss, int se, int p, otype val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = val;
      return;
    }

    int mid = (ss + se) / 2;
    __update(si * 2 + 1, ss, mid, p, val);
    __update(si * 2 + 2, mid + 1, se, p, val);

    otype lhs = tree[si * 2 + 1], rhs = tree[si * 2 + 2];
    tree[si] = {(lhs.first * rhs.second + rhs.first) % MOD, (lhs.second * rhs.second) % MOD};
  }

  otype __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return {0, 1};
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    otype lhs = __query(ss, mid, qs, qe, 2 * si + 1), rhs = __query(mid + 1, se, qs, qe, 2 * si + 2);
    return {(lhs.first * rhs.second + rhs.first) % MOD, (lhs.second * rhs.second) % MOD};
  }

};

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  for (int i = 0; i < n; i++) {
    string op;
    int x;
    cin >> op >> x;
    if (op == "+") a[i] = {x, 1};
    else a[i] = {0, x};
  }
  SegmentTree s(n);

  while (q--) {
    int i, x;
    string op;
    cin >> i >> op >> x;
    if (op == "+") s.update(i - 1, {x, 1});
    else s.update(i - 1, {0, x});
    auto [av, mv] = s.query(0, n - 1);
    cout << av << '\n';
  }
}
