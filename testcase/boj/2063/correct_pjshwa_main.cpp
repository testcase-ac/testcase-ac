#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<double> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];
  sort(A.begin(), A.end());

  for (int i = 1; i < N; i++) {
    double rsum = 0;
    for (int j = 0; j < i; j++) rsum += A[j];

    if (rsum >= A[i]) {
      cout << "YES\n";
      return;
    }
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
