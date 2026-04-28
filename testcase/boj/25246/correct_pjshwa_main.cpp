#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

bool is_vowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void solve() {
  string s;
  cin >> s;
  int n = s.size();
  for (int i = n - 1; i >= 0; i--) {
    if (is_vowel(s[i])) {
      cout << s.substr(0, i + 1) << "ntry\n";
      return;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
