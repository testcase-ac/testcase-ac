#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  int n, m, s;
  map<int, int> atally, ans;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> s;

    while (s % 2 == 0) {
      if (!atally.count(2)) atally[2] = 0;
      atally[2]++;
      s /= 2;
    }

    for (int i = 3; i <= 31623; i += 2) {
      while (s % i == 0) {
        if (!atally.count(i)) atally[i] = 0;
        atally[i]++;
        s /= i;
      }
    }

    if (s > 1) {
      if (!atally.count(s)) atally[s] = 0;
      atally[s]++;
    }
  }

  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> s;

    while (s % 2 == 0) {
      if (atally.count(2) && atally[2]) {
        if (!ans.count(2)) ans[2] = 0;
        atally[2]--;
        ans[2]++;
      }
      s /= 2;
    }

    for (int i = 3; i <= 31623; i += 2) {
      while (s % i == 0) {
        if (atally.count(i) && atally[i]) {
          if (!ans.count(i)) ans[i] = 0;
          atally[i]--;
          ans[i]++;
        }
        s /= i;
      }
    }

    if (s > 1) {
      if (atally.count(s) && atally[s]) {
        if (!ans.count(s)) ans[s] = 0;
        atally[s]--;
        ans[s]++;
      }
    }
  }

  ll fans = 1, mod = 1e9;
  bool modded = false;
  for (auto [el, cnt] : ans) {
    for (int i = 0; i < cnt; i++) {
      if (fans * el >= mod) modded = true;
      fans = (fans * el) % mod;
    }
  }

  string fstr = to_string(fans);
  if (modded) {
    int sz = fstr.size();
    for (int i = 0; i < 9 - sz; i++) fstr = '0' + fstr;
  }
  cout << fstr << '\n';
}
