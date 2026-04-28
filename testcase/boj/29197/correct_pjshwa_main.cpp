#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  set<pii> U;
  for (int i = 0; i < N; i++) {
    int x, y; cin >> x >> y;
    int g = abs(__gcd(x, y));
    U.insert({x / g, y / g});
  }
  cout << U.size() << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
