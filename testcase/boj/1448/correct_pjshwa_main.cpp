#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  sort(A, A + N);

  int ans = -1;
  for (int i = 0; i < N - 2; ++i) {
    if (A[i] + A[i + 1] > A[i + 2]) {
      ans = max(ans, A[i] + A[i + 1] + A[i + 2]);
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
