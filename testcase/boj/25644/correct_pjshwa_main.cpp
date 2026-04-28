#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int INF = 0x3f3f3f3f;

void solve() {
  int N;
  cin >> N;

  int minx = INF, ans = 0;
  for (int i = 0; i < N; i++) {
    int x;
    cin >> x;
    minx = min(minx, x);
    ans = max(ans, x - minx);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
