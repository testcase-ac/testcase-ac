#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int t[MAX];

void solve() {
  int N, K; cin >> N >> K;

  t[0] = 1; int run = 0, ans = 1;
  for (int i = 0; i < N - 1; i++) {
    int x; cin >> x;
    run = (run + x) % K;
    ans = max(ans, ++t[run]);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
