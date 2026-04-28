#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, a, b;
  cin >> n >> a >> b;
  if (n < a + b - 1) return cout << "-1\n", void();

  vector<int> ans;
  if (a > b) {
    for (int i = 1; i < b; i++) ans.push_back(i);
    for (int i = a; i >= 1; i--) ans.push_back(i);
    while (ans.size() < n) ans.push_back(1);
  }
  else {
    if (a == 1) {
      for (int i = 1; i < b; i++) ans.push_back(i);
      while (ans.size() < n - 1) ans.push_back(1);
      ans.push_back(b);
    }
    else {
      for (int i = 1; i <= b; i++) ans.push_back(i);
      for (int i = a - 1; i >= 1; i--) ans.push_back(i);
      while (ans.size() < n) ans.push_back(1);
    }
  }
  reverse(ans.begin(), ans.end());
  for (int e : ans) cout << e << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
