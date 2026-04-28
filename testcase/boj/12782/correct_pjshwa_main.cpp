#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string A, B; cin >> A >> B;
  int N = A.size();

  int z01 = 0, z10 = 0;
  for (int i = 0; i < N; i++) {
    if (A[i] == '0' && B[i] == '1') z01++;
    if (A[i] == '1' && B[i] == '0') z10++;
  }
  cout << max(z01, z10) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
