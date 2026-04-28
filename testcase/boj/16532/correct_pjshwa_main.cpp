#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const ll MAX = 1e5;
ll lp[MAX + 1];
int a[MAX + 1];
vector<int> pr;

class MergeSortTree {

public:
  MergeSortTree(int N) {
    n = N;
    for (flag = 1; flag < N; flag <<= 1);
    tree.resize(2 * flag);
    __init(0, N - 1, 0);
  }

  int query(int L, int R, int val) {
    return __query(0, n - 1, L, R, 0, val);
  }

private:
  int n, flag;
  vector<vector<int>> tree;

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

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  for (ll i = 2; i <= MAX; i++) {
    int n = i;
    for (ll j = 2; j * j <= n; j++) {
      if (n % j) continue;

      int idx = lower_bound(pr.begin(), pr.end(), j) - pr.begin() + 1;
      while (n % j == 0) n /= j;
      a[i] = idx;
    }

    if (n > 1) a[i] = lower_bound(pr.begin(), pr.end(), n) - pr.begin() + 1;
  }

  MergeSortTree mt(MAX + 1);

  int q;
  cin >> q;
  while (q--) {
    int n, k;
    cin >> n >> k;

    auto it = upper_bound(pr.begin(), pr.end(), k);
    if (it == pr.begin()) cout << "0\n";
    else {
      int idx = it - pr.begin();
      int o = mt.query(2, n, idx);
      cout << (n - 1) - o << '\n';
    }
  }
}
