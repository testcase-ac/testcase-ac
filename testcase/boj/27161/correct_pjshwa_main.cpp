#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  int rev = 0, cur = 0;
  for (int i = 0; i < N; i++) {
    string o; int x;
    cin >> o >> x;

    if (rev) cur--;
    else cur++;

    if (cur == 0) cur = 12;
    if (cur == 13) cur = 1;

    if (o == "HOURGLASS") {
      if (x != cur) rev = !rev;

      cout << cur << ' ' << "NO\n";
    }
    else {
      if (x == cur) cout << cur << ' ' << "YES\n";
      else cout << cur << ' ' << "NO\n";
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
