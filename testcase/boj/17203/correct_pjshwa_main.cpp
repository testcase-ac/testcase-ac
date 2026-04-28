#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
int A[MAXN + 1], P[MAXN + 1];

void solve() {
  int N, Q; cin >> N >> Q;
  for (int i = 1; i <= N; ++i) {
    cin >> A[i];
    P[i] = P[i - 1] + abs(A[i] - A[i - 1]);
  }
  while (Q--) {
    int l, r; cin >> l >> r;
    cout << P[r] - P[l] << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
