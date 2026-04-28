#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll Y; cin >> Y;

  if (Y == 1) {
    cout << "2 -3 1\n";
    return;
  }
  if (Y == -1) {
    cout << "2 3 1\n";
    return;
  }

  ll A = 1, B = -Y + (Y > 0 ? 1 : -1), C;
  C = -(A * Y * Y + B * Y);

  cout << A << ' ' << B << ' ' << C << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
