#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int ans = K;
  for (int i = 0; i < N - K + 1; i++) {
    int lstr = i == 0 ? 0 : 1;
    for (int j = i - 2; j >= 0; j--) {
      if (A[j] < A[j + 1]) lstr++;
      else break;
    }
    int rstr = i + K == N ? 0 : 1;
    for (int j = i + K + 1; j < N; j++) {
      if (A[j] > A[j - 1]) rstr++;
      else break;
    }

    int mstr_l = 0, mstr_r = 0;
    for (int j = 0; j < K; j++) {
      if (i == 0 || A[i + j] > A[i - 1]) mstr_l++;
      if (i == N - K || A[i + j] < A[i + K]) mstr_r++;
    }

    if (mstr_l == K && mstr_r == K) ans = max(ans, lstr + rstr + K);
    ans = max(ans, lstr + mstr_l);
    ans = max(ans, rstr + mstr_r);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
