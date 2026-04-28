#include <bits/stdc++.h>
#define ll long long
using namespace std;


void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int a, b, c;
  cin >> a >> b >> c;

  int n = a + 2 * b + 3 * c;
  if (n & 1) cout << "No\n";
  else if (c > a) cout << "No\n";
  else if (c == 0 && a == 0 && (b & 1)) cout << "No\n";
  else cout << "Yes\n";
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
