#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int obc = (N + 1) / 2, ans = 0;
  for (int add = max(1, obc - 100); add <= obc + 100; ++add) {
    string add_b = bitset<32>(add).to_string();

    int bc = obc, carry = 0, c = (N & 1);
    while (!add_b.empty()) {
      int p = add_b.back() - '0'; add_b.pop_back();
      int sum = c + p + carry; carry = sum / 2;
      bc += sum % 2 - c; c ^= 1;
    }
    if (add == bc) ans = add - 1;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
