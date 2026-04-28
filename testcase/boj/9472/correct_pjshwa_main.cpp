#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll D[21];

ll C(int n, int k) {
  ll ret = 1;
  for (int i = 0; i < k; ++i) {
    ret *= n - i;
    ret /= i + 1;
  }
  return ret;
}

ll T(int N, int k) {
  if (N == k) return D[N];

  ll ret = 0;
  for (int i = k; i <= N - 1; ++i) {
    ll cur = C(N - 1 - k, i - k) * D[i];
    ret += cur;
  }
  return ret;
}

ll S(int N, int k) {
  ll ret = 0;
  for (int i = k; i <= N; ++i) {
    ret += T(N, i);
  }
  return ret;
}

void solve() {
  int tc, N, k; cin >> tc >> N >> k;
  cout << tc << ' ' << S(N, k) << '\n';
}

int main() {
  fast_io();

  D[0] = D[2] = 1;
  for (int i = 3; i <= 20; ++i) {
    D[i] = (i - 1) * (D[i - 1] + D[i - 2]);
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
