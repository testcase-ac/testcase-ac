#include <bits/stdc++.h>
using namespace std;
using ll = long long;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll ndigits_upto_n(ll n) {
  string s = to_string(n); ll ret = 0, pw = 1;
  for (int d = 1; d < (int)s.size(); ++d) {
    ret += d * 9 * pw;
    pw *= 10;
  }
  ret += s.size() * (n - pw + 1);
  return ret;
}

int U, K;
void solve() {
  int l = 1, r = U;
  while (l < r) {
    int m = (l + r) / 2;
    if (ndigits_upto_n(m) < U) l = m + 1;
    else r = m;
  }

  string T = "", ans = "";
  for (int i = l; i < l + K; ++i) T += to_string(i);

  int B = ndigits_upto_n(l - 1) + 1;
  for (int i = B; (int)ans.size() < K; ++i) {
    if (i >= U) ans += T[i - B];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> U >> K) {
    if (U == 0 && K == 0) break;
    solve();
  }
}
