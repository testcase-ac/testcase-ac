#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, A, L, R;
  cin >> N >> A >> L >> R;
  if ((__int128_t)L * N > A) return cout << "NO\n", void();

  for (int i = 1; i <= N; i++) {
    if (A % i) continue;
    ll v = A / i;
    if (v < L || v > R) continue;

    cout << "YES\n";
    for (int j = 0; j < i; j++) cout << v << ' ';
    for (int j = 0; j < N - i; j++) cout << L << ' ';
    cout << '\n';
    return;
  }

  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
