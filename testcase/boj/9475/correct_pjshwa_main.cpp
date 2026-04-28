#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using matrix = vector<vector<ll>>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

__int128_t C(int n, int k) {
  __int128_t ans = 1;
  k = min(k, n - k);
  for (int i = 1; i <= k; i++) {
    ans *= (n - i + 1);
    ans /= i;
  }
  return ans;
}

void print128(__int128_t x) {
  if (x == 0) {
    cout << "0";
    return;
  }
  string res;
  while (x > 0) {
    res += (x % 10) + '0';
    x /= 10;
  }
  reverse(res.begin(), res.end());
  cout << res;
}

void solve() {
  int tc, P, N, M; cin >> tc >> P >> N >> M;
  cout << tc << ' ';

  if (N < M) cout << 0;
  else {
    __int128_t ans = C(N, M);
    for (int i = 0; i < N - M; ++i) ans *= P;
    print128(ans);
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
