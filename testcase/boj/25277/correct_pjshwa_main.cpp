#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, ans = 0;
  cin >> n;
  while (n--) {
    string s;
    cin >> s;
    if (s == "he" || s == "she" || s == "him" || s == "her") ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
