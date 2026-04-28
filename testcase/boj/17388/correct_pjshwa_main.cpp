#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int S, K, H;
  cin >> S >> K >> H;

  if (S + K + H >= 100) cout << "OK";
  else {
    int ans = min({S, K, H});
    if (ans == S) cout << "Soongsil";
    else if (ans == K) cout << "Korea";
    else cout << "Hanyang";
  }
  cout << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
