#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  int M = N;
  N = 1 << N;
  vector<int> A(N), B(N);
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    B[i] = A[i];
  }
  sort(B.begin(), B.end());

  for (int i = 0; i < N; i++) {
    int x = upper_bound(B.begin(), B.end(), A[i]) - B.begin(); x--;
    for (int b = 19; b >= 0; b--) {
      if (x >= (1 << b) - 1) {
        cout << M - b << ' ';
        break;
      }
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
