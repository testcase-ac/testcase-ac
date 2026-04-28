#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string add(string a, string b) {
  if (a == "!" || b == "!") return "!";
  int az = a[0] - '0', bz = b[0] - '0';
  if (az + bz >= 10) return "!";
  return to_string(az + bz);
}

void solve() {
  int N; cin >> N; string ans = "0";
  for (int i = 0; i < 2 * N + 1; ++i) {
    string s; cin >> s;
    if (i & 1) continue;
    ans = add(ans, s);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
