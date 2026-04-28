#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3e5;
ll A[MAX + 1], P[MAX + 1];

void solve() {
  int N, K; cin >> N >> K;
  for (int i = 1; i <= N; i++) cin >> A[i], P[i] = P[i - 1] + A[i];
  sort(P + 1, P + N + 1, greater<ll>());

  ll ans = 0;
  for (int i = 1; i <= K; i++) ans += P[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
