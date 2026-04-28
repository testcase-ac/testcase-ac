#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int a, b; cin >> a >> b;
  int g = gcd(a, b);
  a /= g; b /= g;
  int u = b * b, v = a * a + b * b;

  vector<string> ans{"tan", "acos"};
  while (u > 1 || v > 1) {
    if (u * 2 >= v) {
      int t = v - u;
      v = u; u = t;
      ans.push_back("cos");
    } else {
      v -= u;
      ans.push_back("sin");
    }
    ans.push_back("atan");
  }
  ans.push_back("cos");

  reverse(ans.begin(), ans.end());
  cout << ans.size() << '\n';
  for (auto& s : ans) cout << s << ' ';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
