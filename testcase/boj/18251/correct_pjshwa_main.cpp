#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 262'143;
const ll INF = 1e18;
int n, a[MAX + 1];
vector<int> inorder;

void dfs(int v) {
  if (2 * v <= n) dfs(2 * v);
  inorder.push_back(a[v]);
  if (2 * v + 1 <= n) dfs(2 * v + 1);
}

ll max_subarray(vector<int>& sa) {
  ll max_so_far = -INF, max_ending_here = 0;
  for (int i = 0; i < sa.size(); i++) {
    max_ending_here = max_ending_here + sa[i];
    if (max_so_far < max_ending_here) max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;
  }
  return max_so_far;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  dfs(1);

  int h = round(log2(n + 1));
  ll mv = -INF;
  for (int i = 1; i <= h; i++) {
    for (int j = i; j <= h; j++) {
      vector<int> candidates;
      for (int k = 1; k <= n; k++) {
        if (k % (1 << (h - j)) == 0 && k % (1 << (h - i + 1))) candidates.push_back(inorder[k - 1]);
      }
      mv = max(mv, max_subarray(candidates));
    }
  }

  cout << mv;
}
