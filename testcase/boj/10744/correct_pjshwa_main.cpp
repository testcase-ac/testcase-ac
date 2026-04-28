#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 750, MOD = 1000000007;

class SegmentTree {

public:

  void init(vector<int>& ns) {
    nums = ns;
    compress(nums);
    n = nums.size();
    for (flag = 1; flag < n; flag <<= 1);
    tree.resize(2 * flag, 0);
  }

  void add(int P, int val) {
    __add(0, 0, n - 1, lower_bound(all(nums), P) - nums.begin(), val);
  }

  ll query(int R) {
    int ut = upper_bound(all(nums), R) - nums.begin();
    return __query(0, n - 1, 0, ut - 1, 0);
  }

private:
  int n, flag;
  vector<int> tree, nums;

  void __add(int si, int ss, int se, int p, int val) {
    if (ss > se || ss > p || se < p) return;

    if (ss == se) {
      tree[si] = (tree[si] + val) % MOD;
      return;
    }

    int mid = (ss + se) / 2;
    __add(si * 2 + 1, ss, mid, p, val);
    __add(si * 2 + 2, mid + 1, se, p, val);

    tree[si] = (tree[si * 2 + 1] + tree[si * 2 + 2]) % MOD;
  }

  int __query(int ss, int se, int qs, int qe, int si) {
    if (ss > se || ss > qe || se < qs) return 0;
    if (ss >= qs && se <= qe) return tree[si];

    int mid = (ss + se) / 2;
    return (__query(ss, mid, qs, qe, 2 * si + 1) + __query(mid + 1, se, qs, qe, 2 * si + 2)) % MOD;
  }
};

int board[MAX][MAX];
SegmentTree s[MAX * MAX + 1], f;

int main() {
  fast_io();

  int r, c, k;
  cin >> r >> c >> k;
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cin >> board[i][j];

  vector<int> cols[k + 1];
  for (int i = 0; i < r; i++) for (int j = 0; j < c; j++) cols[board[i][j]].push_back(j);
  for (int i = 1; i <= k; i++) if (cols[i].size()) s[i].init(cols[i]);

  vector<int> fv;
  for (int j = 0; j < c; j++) fv.push_back(j);
  f.init(fv);

  f.add(0, 1);
  s[board[0][0]].add(0, 1);

  for (int i = 1; i < r - 1; i++) {
    for (int j = c - 2; j > 0; j--) {
      int val = f.query(j - 1) - s[board[i][j]].query(j - 1);
      if (val < 0) val += MOD;
      f.add(j, val);
      s[board[i][j]].add(j, val);
    }
  }

  int ret = f.query(c - 2) - s[board[r - 1][c - 1]].query(c - 2);
  if (ret < 0) ret += MOD;
  cout << ret << '\n';
}
