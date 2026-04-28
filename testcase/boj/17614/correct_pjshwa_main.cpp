#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
 
void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  int ans = 0;
  for (int i = 1; i <= N; i++) {
    for (char c : to_string(i)) {
      if (c == '3') ans++;
      if (c == '6') ans++;
      if (c == '9') ans++;
    }
  }
  cout << ans << '\n';
}

int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}
