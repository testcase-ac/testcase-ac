#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A(N); ll osum = 0, esum = 0;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    if (i % 2) esum += A[i];
    else osum += A[i];
  }

  if (osum == esum) cout << "0\n";
  else if (N == 3 && osum > esum) cout << "-1\n";
  else cout << abs(osum - esum) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
