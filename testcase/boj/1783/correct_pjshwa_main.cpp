#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, M; cin >> N >> M;
  if (N == 1) return cout << "1\n", void();
  if (N == 2) {
    cout << min(4, (M + 1) / 2) << '\n';
    return;
  }

  if (M == 1) cout << "1\n";
  else if (M == 2) cout << "2\n";
  else if (M == 3) cout << "3\n";
  else if (M <= 6) cout << "4\n";
  else cout << 5 + (M - 7) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
