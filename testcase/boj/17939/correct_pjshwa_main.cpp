#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX], B[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  B[N - 1] = A[N - 1];
  for (int i = N - 2; i >= 0; i--) B[i] = max(A[i], B[i + 1]);

  ll ans = 0;
  for (int i = 0; i < N; i++) ans += B[i] - A[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
