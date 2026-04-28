#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  int A[N];
  for (int i = 0; i < N; ++i) A[i] = S[i] - '0';

  int P[10]{};
  for (int i = 0; i < N; ++i) ++P[A[i]];

  int B[N]{};
  for (int p = 9; p >= 1; --p) {
    int need = 0;
    for (int i = 0; i < N / 2; ++i) {
      if (B[i] > p) continue;

      int j = N - 1 - i;
      if (A[i] != p && A[j] != p) continue;

      need += 2;
      need -= (A[i] == p);
      need -= (A[j] == p);

      B[i] = B[j] = p;
    }

    P[p] -= need;
    for (int i = 0; i < N / 2; ++i) {
      if (B[i] >= p) continue;

      int j = N - 1 - i;
      assert(A[i] != p && A[j] != p);

      if (P[p] >= 2) {
        B[i] = B[j] = p;
        P[p] -= 2;
      }
    }
  }

  if (N & 1) {
    int i = N / 2;
    B[i] = A[i];
    for (int p = 9; p >= 1; --p) {
      if (P[p]) B[i] = max(B[i], p);
    }
  }

  for (int i = 0; i < N; ++i) cout << B[i];
  cout << '\n';

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
