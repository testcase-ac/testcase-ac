#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 70000;
int a[MAX], r[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  if (a[n - 1] < 0) cout << "-1\n";
  else {
    for (int i = 0; i < n; i++) r[i] = n - i;

    bool ostreak = false;
    int ostreak_s;
    for (int i = 0; i < n; i++) {
      if (a[i] < 0 && !ostreak) {
        ostreak = true;
        ostreak_s = i;
      }
      if (a[i] > 0 && ostreak) {
        ostreak = false;
        reverse(r + ostreak_s, r + i + 1);
      }
    }

    for (int i = 0; i < n; i++) cout << r[i] << ' ';
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
