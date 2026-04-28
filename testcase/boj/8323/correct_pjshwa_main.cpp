#include <bits/stdc++.h>
using namespace std;

const int MAX = 2e6;
string A[MAX];

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k;
  cin >> n >> k;

  if (k < n || k > 6 * n) return cout << "0\n", void();

  
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
