#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool nondec(ll n) {
  string s = to_string(n);
  for (int i = 1; i < s.size(); i++) {
    if (s[i - 1] > s[i]) return false;
  }
  return true;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  ll N, pw = 1; cin >> N;
  if (nondec(N)) {
    cout << N << '\n';
    return;
  }

  ll ans, d = to_string(N).size();
  for (int i = 0; i < d; i++) {
    ll r = N % pw;
    if (nondec(N - r - 1)) {
      ans = N - r - 1;
      break;
    }
    pw *= 10;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
