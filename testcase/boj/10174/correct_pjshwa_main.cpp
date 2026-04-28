#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string s;
  getline(cin, s);

  int n = s.size();
  for (int i = 0; i < n; i++) {
    if (s[i] >= 'A' && s[i] <= 'Z') s[i] = s[i] - 'A' + 'a';
  }

  // check if palindrome
  for (int i = 0; i < s.size() / 2; i++) {
    if (s[i] != s[s.size() - 1 - i]) return cout << "No\n", void();
  }
  cout << "Yes\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  cin.ignore();
  while (t--) solve();
}
