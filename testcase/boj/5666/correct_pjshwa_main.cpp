#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

double H, P;
void solve() {
  double ans = H / P;
  cout << fixed << setprecision(2) << ans << '\n';
}

int main() {
  fast_io();

  while (cin >> H >> P) solve();
}
