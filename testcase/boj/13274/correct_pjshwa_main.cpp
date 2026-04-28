#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, K; cin >> N >> K;
  vector<ll> A(N), B(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  while (K--) {
    int l, r, x; cin >> l >> r >> x; l--; r--;
    for (int i = l; i <= r; i++) A[i] += x;

    int i1 = 0, i2 = l, j = 0;
    while (i1 < N && i2 <= r) {
      if (A[i1] < A[i2]) B[j++] = A[i1++];
      else B[j++] = A[i2++];
      if (i1 == l) i1 = r + 1;
    }
    while (i1 < N) {
      B[j++] = A[i1++];
      if (i1 == l) i1 = r + 1;
    }
    while (i2 <= r) B[j++] = A[i2++];
    for (int i = 0; i < N; i++) A[i] = B[i];
  }

  for (int i = 0; i < N; i++) {
    cout << A[i] << " \n"[i == N - 1];
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
