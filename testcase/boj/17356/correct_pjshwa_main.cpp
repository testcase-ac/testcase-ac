#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  double A, B;
  cin >> A >> B;

  double p = 1 + pow(10, (B - A) / 400);
  cout << fixed << setprecision(10) << 1 / p << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}