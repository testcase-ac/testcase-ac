#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_digit(char c) {
  return '0' <= c && c <= '9';
}

bool is_alpha(char c) {
  return 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z';
}

void solve() {
  string S; getline(cin, S);

  int i = 0, N = S.size(), ans = 0;
  while (i < N) {
    if (is_digit(S[i])) {
      while (i < N && is_digit(S[i])) i++;
      ans += 8;
      continue;
    }
    else if (is_alpha(S[i])) {
      int len = 0;
      while (i < N && is_alpha(S[i])) i++, len++;
      ans += len + 12;
      continue;
    }
    else if (S[i] == ']') ans += 8;
    i++;
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
