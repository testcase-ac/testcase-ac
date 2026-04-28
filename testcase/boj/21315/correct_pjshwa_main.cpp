#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1000;
int A[MAX + 1], C[MAX + 1], D[MAX + 1];
int N;

void init() {
  for (int i = 1; i <= N; i++) C[i] = i;
}

void copy() {
  for (int i = 1; i <= N; i++) D[i] = C[i];
}

void paste() {
  for (int i = 1; i <= N; i++) C[i] = D[i];
}

void shuffle_k_range(int l) {
  if (l == 0) return;

  copy();

  for (int i = 1; i <= l / 2; i++) D[i] = C[i + l / 2];
  for (int i = l / 2 + 1; i <= l; i++) D[i] = C[i - l / 2];

  paste();
  shuffle_k_range(l / 2);
}

void shuffle_k(int k) {
  int d = N - (1 << k);
  for (int i = 1; i <= (1 << k); i++) D[i] = C[i + d];
  for (int i = 1; i <= d; i++) D[i + (1 << k)] = C[i];

  paste();
  shuffle_k_range(1 << k);
}

bool ident() {
  for (int i = 1; i <= N; i++) {
    if (A[i] != C[i]) return false;
  }
  return true;
}

void solve() {
  cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];

  for (int k1 = 1;; k1++) {
    if ((1 << k1) >= N) break;

    for (int k2 = 1;; k2++) {
      if ((1 << k2) >= N) break;

      init();

      shuffle_k(k1);
      shuffle_k(k2);

      if (!ident()) continue;

      cout << k1 << ' ' << k2 << '\n';
      // return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
