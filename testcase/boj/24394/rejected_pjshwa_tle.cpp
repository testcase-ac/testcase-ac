#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int LIM = 1e7;

void solve() {
  int n, s;
  cin >> n >> s;

  if (s >= LIM) cout << n * 2 << ' ' << s - LIM << '\n';
  else {
    for (int ni = 0; ni <= 2 * n; ni++) {
      ll cur = ni;
      cur *= LIM;
      cur /= (2 * n);

      if (cur <= s && ni >= 2 * (s - cur)) return cout << ni << ' ' << s - cur << '\n', void();
    }
    cout << "-1\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
