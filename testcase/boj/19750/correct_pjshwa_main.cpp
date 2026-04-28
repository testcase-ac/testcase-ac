#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int l, r; cin >> l >> r;
    --A[l]; ++A[r];
  }

  int lsum = 0, rsum = 0;
  for (int i = 1; i <= MAXN; ++i) {
    if (A[i] < 0) lsum -= A[i];
    else rsum += A[i];
  }
  cout << N + max(lsum, rsum) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
