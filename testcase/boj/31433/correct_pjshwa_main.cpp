#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int N = S.size();

  // K, S, A, K, ...
  int ans = 2 * N;

  // Starts with K
  {
    int cur = 0, state = 0;
    for (int i = 0; i < N; ++i) {
      if (state == 0 && S[i] == 'K') {
        state = (state + 1) % 3;
        ++cur;
      }
      if (state == 1 && S[i] == 'S') {
        state = (state + 1) % 3;
        ++cur;
      }
      if (state == 2 && S[i] == 'A') {
        state = (state + 1) % 3;
        ++cur;
      }
    }
    ans = min(ans, 2 * (N - cur));
  }

  // Starts with S
  {
    int cur = 0, state = 1;
    for (int i = 0; i < N; ++i) {
      if (state == 0 && S[i] == 'K') {
        state = (state + 1) % 3;
        ++cur;
      }
      if (state == 1 && S[i] == 'S') {
        state = (state + 1) % 3;
        ++cur;
      }
      if (state == 2 && S[i] == 'A') {
        state = (state + 1) % 3;
        ++cur;
      }
    }
    cur = min(cur, N - 1);
    ans = min(ans, 2 * (N - cur));
  }

  // Starts with A
  {
    int cur = 0, state = 2;
    for (int i = 0; i < N; ++i) {
      if (state == 0 && S[i] == 'K') {
        state = (state + 1) % 3;
        ++cur;
      }
      if (state == 1 && S[i] == 'S') {
        state = (state + 1) % 3;
        ++cur;
      }
      if (state == 2 && S[i] == 'A') {
        state = (state + 1) % 3;
        ++cur;
      }
    }
    cur = min(cur, N - 2);
    ans = min(ans, 2 * (N - cur));
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
