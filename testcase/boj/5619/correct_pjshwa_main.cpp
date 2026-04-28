#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a.begin(), a.end());

  vector<int> candidates;
  int z = min(4, n);
  for (int i = 0; i < z; i++) for (int j = 0; j < z; j++) {
    if (i == j) continue;

    int c = stoi(to_string(a[i]) + to_string(a[j]));
    candidates.push_back(c);
  }
  sort(candidates.begin(), candidates.end());

  cout << candidates[2] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
