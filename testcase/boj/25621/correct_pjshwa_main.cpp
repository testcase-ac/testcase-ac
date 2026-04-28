#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 3e5, MOD = 1e9 + 7, INF = 1e18;
int C[MAXN];

void solve() {
  ll N, O, ans; cin >> N >> O; ans = O;
  bool is_inf = false; __int128_t K = O;
  for (int i = 0; i < N; ++i) {
    string s1, s2; cin >> s1 >> s2;
    char sign1 = s1[0], sign2 = s2[0];
    ll val1 = stoi(s1.substr(1)), val2 = stoi(s2.substr(1));
    int choice = 0;

    if (sign1 == sign2) {
      if (sign1 == '+') choice = val1 < val2;
      if (sign1 == '-') choice = val1 > val2;
      if (sign1 == '*') choice = val1 < val2;
    } else {
      if (sign1 == '+' && sign2 == '-') choice = 0;
      if (sign1 == '+' && sign2 == '*') {
        if (is_inf) choice = val2 > 1;
        else choice = K + val1 < K * val2;
      }
      if (sign1 == '-' && sign2 == '+') choice = 1;
      if (sign1 == '-' && sign2 == '*') choice = val2 > 0;
      if (sign1 == '*' && sign2 == '+') {
        if (is_inf) choice = val1 <= 1;
        else choice = K * val1 < K + val2;
      }
      if (sign1 == '*' && sign2 == '-') choice = val1 == 0;
    }

    char sign; ll val;
    if (choice) sign = sign2, val = val2;
    else sign = sign1, val = val1;

    bool is_zero = false;
    if (is_inf) {
      if (sign == '*' && val == 0) is_inf = false, is_zero = true, K = 0;
    } else {
      if (sign == '+') K += val;
      if (sign == '-') K -= val;
      if (sign == '*') K *= val;
      if (K >= INF) is_inf = true;
      if (K <= 0) K = 0, is_zero = true;
    }

    if (is_zero) ans = 0;
    else {
      if (sign == '+') ans = (ans + val) % MOD;
      if (sign == '-') ans = (ans - val + MOD) % MOD;
      if (sign == '*') ans = (ans * val) % MOD;
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
