#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  int oc = 0, ec = 0;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    if (x & 1) oc++;
    else ec++;
  }

  int ans;
  if (oc > ec) {
    ans = ec;
    oc -= ec;
    ans += oc / 2;
  }
  else ans = oc;

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
