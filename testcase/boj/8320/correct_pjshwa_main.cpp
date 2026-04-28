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
    int l = N / i;
    if (l < i) break;

    ans += l - (i - 1);
  }
  cout << ans << '\n';
}
 
int main() {
  fast_io();
 
  int t = 1;
  // cin >> t;
  while (t--) solve();
}