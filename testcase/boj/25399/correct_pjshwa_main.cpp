#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  ll N;
  cin >> N;

  if (N == 0) {
    cout << "3\n";
    cout << "+ 5\n";
    cout << "- 4\n";
    cout << "- 3\n";
    return;
  }
  if (N == 2) {
    cout << "3\n";
    cout << "+ 6\n";
    cout << "- 5\n";
    cout << "- 3\n";
    return;
  }
  if (N == -2) {
    cout << "3\n";
    cout << "- 6\n";
    cout << "+ 5\n";
    cout << "+ 3\n";
    return;
  }

  bool minus = N < 0;
  N = abs(N);

  vector<pll> ans;
  ll Q = sqrt(N);
  if (Q * Q == N) ans.push_back({+1, Q});
  else {
    bool f = false;

    for (ll i = 1; i * i <= N; i++) {
      ll m = N - i * i;
      if (i * i == m) continue;

      ll q = sqrt(m);
      if (q * q == m) {
        ans.push_back({+1, i});
        ans.push_back({+1, q});
        f = true;
        break;
      }
    }

    if (!f) {
      for (ll i = 1; i * i <= N; i++) {
        if (N % i) continue;

        ll r = N / i;
        if ((i + r) & 1) continue;

        ll a = (r + i) / 2, b = (r - i) / 2;
        if (a <= 0 || b <= 0) continue;

        ans.push_back({+1, a});
        ans.push_back({-1, b});
        f = true;
        break;
      }
    }

    if (!f) {
      ans.push_back({-1, 1});
      N++;

      for (ll i = 1; i * i <= N; i++) {
        if (N % i) continue;

        ll r = N / i;
        if ((i + r) & 1) continue;

        ll a = (r + i) / 2, b = (r - i) / 2;
        if (a <= 1 || b <= 1) continue;

        ans.push_back({+1, a});
        ans.push_back({-1, b});
        break;
      }
    }
  }

  if (minus) {
    for (auto& [sign, x] : ans) sign = -sign;
  }

  cout << ans.size() << '\n';
  for (auto& [sign, x] : ans) {
    if (sign == 1) cout << "+ ";
    else cout << "- ";
    cout << x << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
