#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int P, N;
  cin >> P >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  if (P == 200) return cout << "0\n", void();

  for (int i = 0; i < N; i++) {
    P += A[i];
    if (P >= 200) {
      cout << i + 1 << '\n';
      return;
    }
  }
  cout << N << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
