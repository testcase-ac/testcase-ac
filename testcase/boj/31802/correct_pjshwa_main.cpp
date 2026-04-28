#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int modint(int x, int m) {
  return (x % m + m) % m;
}

void solve() {
  int N; cin >> N;
  vector<int> A(N), pi(N);
  for (int i = 0; i < N; ++i) cin >> A[i];
  int a, b; cin >> a >> b;

  int V = N;
  ll rep = (b - a) / V, repv = 0;
  for (int i = 0; i < V; ++i) repv += A[i];

  ll ans = rep * repv;
  int t = modint(b, V);
  while (1) {
    int s = modint(a, V);
    if (s == t) break;
    ans += A[s]; ++a;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
