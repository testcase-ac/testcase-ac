#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ld = long double;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX], B[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int i = 0; i < N; ++i) {
    for (int j : {i - 1, i, i + 1}) {
      if (j < 0 || j >= N) continue;
      if (A[i] == 0 || B[j] >= 1) continue;

      A[i] -= 1; B[j] += 1;
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) ans += B[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
