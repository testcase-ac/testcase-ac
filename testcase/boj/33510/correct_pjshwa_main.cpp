#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, carry = 0, ans = 0; string S; cin >> N >> S;
  for (int i = N - 1; i > 0; --i) {
    int sum = S[i] - '0' + carry;
    ans += (sum & 1);
    carry = (sum + 1) / 2;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
