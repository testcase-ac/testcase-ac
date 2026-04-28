#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n;
  string s;
  cin >> n >> s;

  bool sw;
  int mcnt, ans = 1e9 + 7;

  // Blue ball, move to left
  sw = false, mcnt = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'R') sw = true;
    if (sw && s[i] == 'B') mcnt++;
  }
  ans = min(ans, mcnt);

  // Blue ball, move to right
  sw = false, mcnt = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == 'R') sw = true;
    if (sw && s[i] == 'B') mcnt++;
  }
  ans = min(ans, mcnt);

  // Red ball, move to left
  sw = false, mcnt = 0;
  for (int i = 0; i < n; i++) {
    if (s[i] == 'B') sw = true;
    if (sw && s[i] == 'R') mcnt++;
  }
  ans = min(ans, mcnt);

  // Red ball, move to right
  sw = false, mcnt = 0;
  for (int i = n - 1; i >= 0; i--) {
    if (s[i] == 'B') sw = true;
    if (sw && s[i] == 'R') mcnt++;
  }
  ans = min(ans, mcnt);

  cout << ans << '\n';
}
