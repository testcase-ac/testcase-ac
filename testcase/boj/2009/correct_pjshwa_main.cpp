#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
char H[MAX + 1][MAX + 1], R[MAX + 1][MAX + 1], C[MAX + 1][MAX + 1];
bool ans[MAX + 1][MAX + 1][MAX + 1];

void solve() {
  int n; cin >> n;
  for (int i = 0; i < n; ++i) cin >> H[i];
  for (int i = 0; i < n; ++i) cin >> R[i];
  for (int i = 0; i < n; ++i) cin >> C[i];

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) {
        ans[i][j][k] = (H[j][k] == '1' && R[i][k] == '1' && C[i][j] == '1');
      }
    }
  }

  // Verify H
  for (int j = 0; j < n; ++j) {
    for (int k = 0; k < n; ++k) {
      bool f = false;
      for (int i = 0; i < n; ++i) f |= ans[i][j][k];
      if (f != (H[j][k] == '1')) return cout << "NO\n", void();
    }
  }

  // Verify R
  for (int i = 0; i < n; ++i) {
    for (int k = 0; k < n; ++k) {
      bool f = false;
      for (int j = 0; j < n; ++j) f |= ans[i][j][k];
      if (f != (R[i][k] == '1')) return cout << "NO\n", void();
    }
  }

  // Verify C
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      bool f = false;
      for (int k = 0; k < n; ++k) f |= ans[i][j][k];
      if (f != (C[i][j] == '1')) return cout << "NO\n", void();
    }
  }

  cout << "YES\n";
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      for (int k = 0; k < n; ++k) cout << ans[i][j][k];
      cout << '\n';
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
