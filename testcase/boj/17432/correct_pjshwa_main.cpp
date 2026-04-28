#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve_for(ll N, ll M) {
  if (M >= N - 1) {
    cout << N << ' ';
    if (N > 1) solve_for(N - 1, M - (N - 1));
  }
  else {
    vector<int> A(N);
    iota(A.begin(), A.end(), 1);
    for (int j = N - 1;; j--) {
      if (M == 0) break;
      swap(A[j], A[j - 1]);
      M--;
    }
    for (int e : A) cout << e << ' ';
  }
}

void solve() {
  ll N, M; cin >> N >> M;
  solve_for(N, M);
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
