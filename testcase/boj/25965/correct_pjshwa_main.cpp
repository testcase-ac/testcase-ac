#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;
  vector<tii> A(N);
  for (int i = 0; i < N; ++i) {
    int x, y, z;
    cin >> x >> y >> z;
    A[i] = {x, y, z};
  }

  ll k, d, a;
  cin >> k >> d >> a;

  ll ans = 0;
  for (int i = 0; i < N; ++i) {
    auto [x, y, z] = A[i];
    ll add = k * x - d * y + a * z;
    if (add < 0) continue;
    ans += add;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
