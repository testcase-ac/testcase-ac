#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n; cin >> n;
  vector<int> A(n);
  for (int i = 0; i < n; i++) cin >> A[i];

  vector<int> L{A[0]};
  for (int i = 1; i < n; i++) {
    if (A[i] > L.back()) L.push_back(A[i]);
    else *lower_bound(L.begin(), L.end(), A[i]) = A[i];
  }
  cout << L.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
