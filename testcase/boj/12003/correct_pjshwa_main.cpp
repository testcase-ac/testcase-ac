#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K;
  cin >> N >> K;

  vector<int> A(N), dl(N), dr(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  int r = 0;
  for (int l = 0; l < N; l++) {
    while (r < N && A[r] - A[l] <= K) {
      dl[r] = max(dl[r], r - l + 1);
      r++;
    }
  }
  for (int i = 1; i < N; i++) dl[i] = max(dl[i], dl[i - 1]);

  int l = N - 1;
  for (int r = N - 1; r >= 0; r--) {
    while (l >= 0 && A[r] - A[l] <= K) {
      dr[l] = max(dr[l], r - l + 1);
      l--;
    }
  }
  for (int i = N - 2; i >= 0; i--) dr[i] = max(dr[i], dr[i + 1]);

  int ans = dl[N - 1];
  for (int i = 0; i < N - 1; i++) {
    ans = max(ans, dl[i] + dr[i + 1]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
