#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, J; cin >> N >> M >> J;
  M--;

  int pos = 1, ans = 0;
  while (J--) {
    int x; cin >> x;
    if (x > pos + M) {
      int mov = x - pos - M;
      ans += mov;
      pos += mov;
    }
    else if (x < pos) {
      int mov = pos - x;
      ans += mov;
      pos -= mov;
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
