#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string S;
  cin >> S;
  int N = S.size();

  int ans = 1, l = 0, r = N - 1;
  while (l < r) {
    if (S[l] != S[r]) {
      cout << "0 " << ans << '\n';
      return;
    }

    ans++;
    l++;
    r--;
  }

  cout << "1 " << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
