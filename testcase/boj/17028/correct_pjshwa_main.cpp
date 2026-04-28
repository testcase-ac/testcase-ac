#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  int pre = 1;
  for (int i = N - 2; i >= 0; i--) {
    if (A[i] < A[i + 1]) pre++;
    else break;
  }
  cout << N - pre << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
