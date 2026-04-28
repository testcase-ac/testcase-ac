#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve(int tc) {
  string s, t;
  cin >> s >> t;
  int n = s.size(), ans;

  int zc = 0, oc = 0, qc = 0, tzc = 0, toc = 0;
  for (char c : s) {
    if (c == '0') zc++;
    else if (c == '1') oc++;
    else qc++;
  }
  for (char c : t) {
    if (c == '0') tzc++;
    else if (c == '1') toc++;
  }
  if (oc > toc) ans = -1;
  else {
    int q2z = tzc - zc;
    int q2o = toc - oc;

    ans = 0;
    for (int i = 0; i < n; i++) {
      if (s[i] == '?') {
        if (q2z && t[i] == '0') s[i] = '0', q2z--, ans += 2;
        if (q2o && t[i] == '1') s[i] = '1', q2o--, ans += 2;
      }
    }

    for (int i = 0; i < n; i++) {
      if (s[i] == '?') {
        if (q2z) s[i] = '0', q2z--, ans += 2;
        else if (q2o) s[i] = '1', q2o--, ans += 2;
      }
    }

    for (int i = 0; i < n; i++) {
      if (q2o && s[i] == '0' && t[i] == '1') s[i] = '1', q2o--, ans += 2;
    }

    for (int i = 0; i < n; i++) {
      if (q2o && s[i] == '0') s[i] = '1', q2o--, ans += 2;
    }

    for (int i = 0; i < n; i++) if (s[i] != t[i]) ans++;

    ans /= 2;
  }

  cout << "Case " << tc << ": " << ans << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  for (int tc = 1; tc <= t; tc++) solve(tc);
}
