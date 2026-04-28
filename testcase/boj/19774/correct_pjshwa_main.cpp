#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n;
  cin >> n;

  int a = n % 100, b = n / 100;
  if ((a * a + b * b) % 7 == 1) cout << "YES\n";
  else cout << "NO\n";
}

int main() {
  fast_io();
 
  int t = 1;
  cin >> t;
  while (t--) solve();
}
