#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 5e5, MOD = 1e9 + 7;
int A[MAX];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  ll l = A[0], streak = 1, ans = 1;
  for (int i = 1; i < N; i++) {
    if (A[i] <= l) streak++;
    else {
      ans = (ans * (streak + 1)) % MOD;
      l = A[i]; streak = 1;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
