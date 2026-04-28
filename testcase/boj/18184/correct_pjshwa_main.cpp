#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, k;
  cin >> n >> k;

  cout << "YES\n";
  vector<int> ans;
  if ((1 << n) == k) {
    k--;
    ans.push_back(0);
  }
  for (int i = 0; i < n; i++) {
    if (k & 1) {
      for (int j = (1 << i); j < (1 << i + 1); j++) ans.push_back(j);
    }
    k >>= 1;
  }
  sort(ans.begin(), ans.end());
  for (int el : ans) cout << el << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
