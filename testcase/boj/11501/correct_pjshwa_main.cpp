#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  vector<int> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  ll l = 0, acc = 0, acc_z = 0, ans = 0;
  for (int i = N - 1; i >= 0; i--) {
    if (A[i] <= l) {
      acc += A[i];
      acc_z++;
    }
    else {
      ans += l * acc_z - acc;
      l = A[i];
      acc = acc_z = 0;
    }
  }
  
  ans += l * acc_z - acc;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
