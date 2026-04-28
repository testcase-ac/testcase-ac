#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool needs_red(char c) {
  return c == 'R' || c == 'O' || c == 'P' || c == 'A';
}

bool needs_yellow(char c) {
  return c == 'Y' || c == 'O' || c == 'G' || c == 'A';
}

bool needs_blue(char c) {
  return c == 'B' || c == 'P' || c == 'G' || c == 'A';
}

int tc;

void solve() {
  int n;
  string s;
  cin >> n >> s;

  int rc = 0, yc = 0, bc = 0;
  for (int i = 0; i < n; i++) {
    if (needs_red(s[i]) && (i == 0 || !needs_red(s[i - 1]))) rc++;
    if (needs_yellow(s[i]) && (i == 0 || !needs_yellow(s[i - 1]))) yc++;
    if (needs_blue(s[i]) && (i == 0 || !needs_blue(s[i - 1]))) bc++;
  }

  cout << "Case #" << ++tc << ": " << rc + yc + bc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
