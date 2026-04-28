#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  for (int i = 0; i < N - 2; i++) {
    if (i == N - 3) A[0]--, A[N - 1]--;
    else if (A[0] > A[N - 1]) A[0]--;
    else A[N - 1]--;
  }
  cout << max(A[0], A[N - 1]) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
