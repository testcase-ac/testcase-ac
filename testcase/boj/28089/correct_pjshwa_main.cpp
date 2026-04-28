#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e6;
int A[MAX];

void solve() {
  int N, M; ll K; cin >> N >> M >> K;
  while (M--) {
    int x; cin >> x;
    A[x] = 1;
  }

  int g = 1;
  while (K) {
    if (K & 1) {
      int B[N]{};
      for (int i = 0; i < N; i++) {
        if (!A[i]) continue;

        int x1 = (i - g + N) % N, x2 = (i + g) % N;
        B[x1] ^= 1; B[x2] ^= 1;
      }
      copy(B, B + N, A);
    }
    K >>= 1; g = (g * 2) % N;
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    // cout << A[i] << ' ';
    ans += A[i];
  }
  // cout << '\n';

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
