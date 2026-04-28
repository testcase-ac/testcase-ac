#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  string s;
  cin >> s;

  map<int, int> u;
  u[0] = -1;

  int state = 0, ans = 0, si = -1, ei = -1;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == 'S') state -= 2;
    if (s[i] == 'K') state++;

    if (u.count(state)) {
      if (ans < i - u[state]) {
        ans = i - u[state];
        si = u[state] + 1;
        ei = i;
      }
    }
    else u[state] = i;
  }

  bool able = true;
  int sc = 0, kc = 0;
  for (int i = si; i <= ei; i++) {
    if (s[i] == 'S') sc++;
    if (s[i] == 'K') kc++;
  }

  if (sc == 0 && kc == 0) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
