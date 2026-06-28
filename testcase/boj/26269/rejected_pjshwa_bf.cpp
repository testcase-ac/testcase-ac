#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool next_repetition(int C[], int N, int K) {
  int i = K - 1;
  while (i >= 0 && C[i] == N - 1) i--;
  if (i < 0) return false;

  C[i]++;
  for (int j = i + 1; j < K; j++) C[j] = 0;
  return true;
}

void solve() {
  ll N; cin >> N;
  for (int L = 2 * N - 1; L < 20; L++) {
    int A[L]{};
    do {

      bool f = true;
      for (int x = 0; x < N; x++) {
        int cnt = 0;
        for (int i = 0; i < L; i++) {
          if (A[i] == x) cnt++;
        }
        f &= cnt > 0;
      }
      if (!f) continue;

      for (int x = 1; x < N; x++) {
        int cnt_l = 0, cnt_r = 0;
        for (int i = 0; i < L; i++) {
          if (A[i] != x) continue;

          for (int j = 0; j < i; j++) {
            if (A[j] == x - 1) cnt_l++;
          }
          for (int j = i + 1; j < L; j++) {
            if (A[j] == x - 1) cnt_r++;
          }

          f &= (cnt_l == cnt_r);
        }
      }
      if (!f) continue;

      for (int i = 0; i < L; i++) cout << A[i] + 1 << ' ';
      cout << endl;

    } while (next_repetition(A, N, L));
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
