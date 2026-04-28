#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s[4];

bool consec() {
  int p[4] = {0, 1, 2, 3};

  bool able = false;
  do {
    able |= (
      s[p[0]][0] + 1 == s[p[1]][0] &&
      s[p[1]][0] + 1 == s[p[2]][0] &&
      s[p[0]][1] == s[p[1]][1] && s[p[1]][1] == s[p[2]][1]
    );
  } while (next_permutation(p, p + 4));

  return able;
}

void solve() {
  cin >> s[0] >> s[1] >> s[2] >> s[3];

  bool able = false;
  able |= (s[0] == s[1] && s[1] == s[2]);
  able |= (s[0] == s[1] && s[1] == s[3]);
  able |= (s[0] == s[2] && s[2] == s[3]);
  able |= (s[1] == s[2] && s[2] == s[3]);
  able |= (s[0] == s[1] && s[2] == s[3]);
  able |= (s[0] == s[2] && s[1] == s[3]);
  able |= (s[0] == s[3] && s[1] == s[2]);
  able |= consec();

  if (able) cout << ":)\n";
  else cout << ":(\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
