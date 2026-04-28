#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll a, b, c, d; cin >> a >> b >> c >> d;
  int At[10]{}, Bt[10]{};

  string a_str = to_string(a); int az = a_str.size();
  string b_str = to_string(b); int bz = b_str.size();

  for (int s = 0; s < (1 << az); ++s) {
    string u_str = "";

    fill(At, At + 10, 0);
    for (int i = 0; i < az; ++i) {
      if (s & (1 << i)) u_str += a_str[i];
      else ++At[a_str[i] - '0'];
    }
    if (u_str.empty() || u_str[0] == '0') continue;

    __int128_t u = stoll(u_str);
    if (u * d % c) continue;

    string b_pr_str = ""; auto b_pr = u * d / c;
    while (b_pr) {
      b_pr_str += b_pr % 10 + '0';
      b_pr /= 10;
    }
    reverse(b_pr_str.begin(), b_pr_str.end());
    if (b_pr_str[0] == '0') continue;

    fill(Bt, Bt + 10, 0); int j = 0, b_pr_z = b_pr_str.size();
    for (int i = 0; i < bz; ++i) {
      if (j < b_pr_z && b_pr_str[j] == b_str[i]) ++j;
      else ++Bt[b_str[i] - '0'];
    }
    if (j != b_pr_z) continue;

    int ok = 1;
    for (int i = 0; i < 10; ++i) ok &= At[i] == Bt[i];
    if (ok) {
      cout << "possible\n";
      cout << u_str << ' ' << b_pr_str << '\n';
      return;
    }
  }

  cout << "impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
