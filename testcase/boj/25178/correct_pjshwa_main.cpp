#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX], b[MAX];

bool is_vowel(char c) {
  return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void solve() {
  int n; string s, t;
  cin >> n >> s >> t;
  string so = "", to = "";
  for (int i = 0; i < n; i++) {
    if (!is_vowel(s[i])) so += s[i];
    if (!is_vowel(t[i])) to += t[i];
  }

  if (so != to) return cout << "NO\n", void();
  if (s[0] != t[0] || s[n - 1] != t[n - 1]) return cout << "NO\n", void();

  sort(s.begin(), s.end());
  sort(t.begin(), t.end());
  if (s != t) return cout << "NO\n", void();

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
