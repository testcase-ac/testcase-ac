#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  vector<int> A(N + 1);
  for (int i = 1; i <= N; i++) cin >> A[i];

  int cnt = 0;
  for (int j = 2; j <= N; j++) {
    int x = A[j]; int i = j - 1;
    while (i >= 1 && A[i] > x) {
      cnt++;
      A[i + 1] = A[i];
      i--;
    }
    A[i + 1] = x;
  }
  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
