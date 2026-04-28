#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int f;
void put(int u) {
  u = u ^ f;
  cout << (u ? 'b' : 'a');
}

void solve() {
  int N, M; cin >> N >> M;
  if (N < M) f = 1, swap(N, M);
  N += M;

  if (N <= 10) {
    int mscore = -1, mstate = 0;
    for (int s = 0; s < (1 << N); s++) {
      int cnt = __builtin_popcount(s);
      if (cnt != M) continue;

      int cscore = 0;
      for (int k = 1; k <= N; k++) {
        int f = 0;
        for (int i = 0; i < N; i++) {
          int b = (s >> i) & 1;
          if (i - k >= 0) {
            int nb = (s >> (i - k)) & 1;
            f |= b == nb;
          }
          if (i + k < N) {
            int nb = (s >> (i + k)) & 1;
            f |= b == nb;
          }
        }
        if (f) cscore += k;
      }

      if (cscore > mscore) {
        mscore = cscore;
        mstate = s;
      }
    }

    cout << mscore << '\n';
    for (int i = 0; i < N; i++) put((mstate >> i) & 1);
  }
  else {
    cout << N * (N - 1) / 2 << '\n';
    if (N - M == M) {
      put(0);
      for (int i = 0; i < M - 3; i++) put(1);
      put(0);
      for (int i = 0; i < 3; i++) put(1);
      for (int i = 0; i < N - M - 2; i++) put(0);
    }
    else if (N - M == M + 1) {
      put(0);
      for (int i = 0; i < M - 2; i++) put(1);
      put(0);
      for (int i = 0; i < 2; i++) put(1);
      for (int i = 0; i < N - M - 2; i++) put(0);
    }
    else {
      put(0);
      for (int i = 0; i < M; i++) put(1);
      for (int i = 0; i < N - M - 1; i++) put(0);
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
