#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int a, b, c;
void solve() {
  if (c - b == b - a) cout << "AP " << c + (b - a) << '\n';
  else cout << "GP " << c * (b / a) << '\n';
}

int main() {
  fast_io();
 
  while (cin >> a >> b >> c) {
    if (a == 0 && b == 0 && c == 0) break;
    solve();
  }
}
