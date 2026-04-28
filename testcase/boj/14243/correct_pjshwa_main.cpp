#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;
  int t[3] = {0, 0, 0};
  for (char& c : s) {
    if (c == 'A') t[0]++;
    else if (c == 'B') t[1]++;
    else t[2]++;
  }

  char ans[s.size() + 1];
  memset(ans, 0, sizeof(ans));

  for (int i = 0; i < s.size(); i += 3) {
    if (t[2]) ans[i] = 'C', t[2]--;
  }
  for (int i = 1; i < s.size(); i++) {
    if (ans[i - 1] == 'B') continue;
    if (ans[i]) continue;
    if (t[1]) ans[i] = 'B', t[1]--;
  }
  for (int i = 0; i < s.size(); i++) {
    if (ans[i]) continue;
    if (t[0]) ans[i] = 'A', t[0]--;
  }

  if (t[0] || t[1] || t[2]) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
