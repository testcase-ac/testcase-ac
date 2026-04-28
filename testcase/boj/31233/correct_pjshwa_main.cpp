#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
int A[MAXN], B[3];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  int ans = 0;
  for (int i = 0; i < N - 1; ++i) ans = max(ans, min(A[i], A[i + 1]));
  for (int i = 0; i < N - 2; ++i) {
    for (int j = 0; j < 3; ++j) B[j] = A[i + j];
    sort(B, B + 3);
    ans = max(ans, B[1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
