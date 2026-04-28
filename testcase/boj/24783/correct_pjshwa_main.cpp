#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int a, b, c;
  cin >> a >> b >> c;
  if (a + b == c || a - b == c || b - a == c || a * b == c) cout << "Possible\n";
  else if (a % b == 0 && a / b == c) cout << "Possible\n";
  else if (b % a == 0 && b / a == c) cout << "Possible\n";
  else cout << "Impossible\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
