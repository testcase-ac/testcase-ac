#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
ll A[MAX + 1], d[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; i++) cin >> A[i];
  sort(A + 1, A + N + 1, greater<>());

  for (int i = 1; i <= N; i++) {
    d[i]++; d[i + A[i]]--;
  }
  for (int i = 1; i <= N; i++) d[i] += d[i - 1];

  int ans = 0;
  for (int i = 1; i <= N; i++) ans += d[i] > 0;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
