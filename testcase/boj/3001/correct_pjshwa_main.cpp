#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

ll d[20][150][2];
string S; int M;

ll r(int i, int rem, int f) {
  if (i == S.size()) return rem == 0;
  if (d[i][rem][f] != -1) return d[i][rem][f];

  ll ret = 0, c = S[i] - '0';
  if (f) {
    for (int j = 0; j <= c; j++) {
      if (rem >= j) ret += r(i + 1, rem - j, c == j);
    }
  }
  else {
    for (int j = 0; j <= 9; j++) {
      if (rem >= j) ret += r(i + 1, rem - j, 0);
    }
  }

  return d[i][rem][f] = ret;
}

ll solve(ll A, ll B) {
  S = to_string(A - 1);
  memset(d, -1, sizeof(d));
  ll ret1 = r(0, M, 1);

  S = to_string(B);
  memset(d, -1, sizeof(d));
  ll ret2 = r(0, M, 1);

  return ret2 - ret1;
}

void solve() {
  ll A, B;
  cin >> A >> B >> M;

  ll ans = solve(A, B);
  ll left = A, right = B + 1;
  while (left < right) {
    ll mid = (left + right) / 2;

    if (solve(mid, B) == ans) left = mid + 1;
    else right = mid;
  }

  cout << ans << '\n' << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
