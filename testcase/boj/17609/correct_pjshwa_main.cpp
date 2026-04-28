#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s;

bool is_palindrome(int si, int ei) {
  int size = ei - si + 1;
  if (size <= 1) return true;
  return s[si] == s[ei] && is_palindrome(si + 1, ei - 1);
}

bool is_pseudo_palindrome(int si, int ei) {
  int size = ei - si + 1;
  if (size <= 2) return true;
  if (s[si] == s[ei]) return is_pseudo_palindrome(si + 1, ei - 1);
  else return is_palindrome(si, ei - 1) || is_palindrome(si + 1, ei);
}

void solve() {
  cin >> s;
  if (is_palindrome(0, s.size() - 1)) cout << 0;
  else if (is_pseudo_palindrome(0, s.size() - 1)) cout << 1;
  else cout << 2;
  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
