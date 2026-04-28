#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, s, m;
  cin >> n >> s >> m;

  for (int n1 = 11; n1 <= 22; n1++) {
    int cur = 0;
    for (int n3 = 10; n3 <= n; n3++) {
      if (n3 >= 11 && n3 <= 22) continue;

      int n2 = s;
      int num = n1 * 1000 + n2 * 100 + n3 % 100;
      if (num % (n1 + n2) && num % (n1 + n3) && num % (n2 + n3)) continue;

      cur++;
    }

    cout << cur << '\n';
  }

  for (int n3 = 10; n3 <= n; n3++) {
    if (n3 >= 11 && n3 <= 22) continue;

    int n1 = m + 10, n2 = s;
    int num = n1 * 1000 + n2 * 100 + n3 % 100;
    if (num % (n1 + n2) && num % (n1 + n3) && num % (n2 + n3)) continue;

    cout << n1 << ' ' << n2 << ' ' << n3 << '\n';
    return;
  }

  cout << "0 0 0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
