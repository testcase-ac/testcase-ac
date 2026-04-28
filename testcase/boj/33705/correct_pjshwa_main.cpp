#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN + 1], C[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> A[i];

  // Check 0
  for (int i = 1; i <= N; ++i) ++C[A[i]];
  if (C[1] >= (N + 1) / 2) return cout << "0\n", void();

  // Check 1
  memset(C, 0, sizeof(C));
  for (int i = 1; i <= N; ++i) {
    ++C[A[i]];
    int w = (i + 1) / 2;
    if (C[1] >= w) return cout << "1\n", void();
  }
  memset(C, 0, sizeof(C));
  for (int i = N; i >= 1; --i) {
    ++C[A[i]];
    int w = (N - i + 2) / 2;
    if (C[1] >= w) return cout << "1\n", void();
  }

  cout << "2\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
