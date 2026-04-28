#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n, tc;
void solve() {
  int p = 5, ans = 0;
  while (p <= n) {
    ans += n / p;
    p *= 5;
  }
  cout << "Case #" << ++tc << ": " << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> n;
    if (n == 0) break;
    solve();
  }

}
