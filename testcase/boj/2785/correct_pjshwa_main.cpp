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
  sort(A.begin(), A.end());

  int acc = 0;
  for (int i = 0; i < N; i++) {
    acc += A[i];
    if (acc >= N - i - 2) {
      int ans = N - i - 2;
      if (acc > N - i - 2) ans++;
      return cout << ans << '\n', void();
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
