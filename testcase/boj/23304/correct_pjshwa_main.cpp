#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s;

bool is_palindrome(int si, int ei) {
  int size = ei - si + 1;
  if (size <= 1) return true;
  for (int st = si; st <= ei; st++) {
    if (s[st] != s[ei - st + si]) return false;
  }
  return true;
}

bool is_akaraka_palindrome(int si, int ei) {
  int size = ei - si + 1;
  if (size <= 1) return true;
  return is_palindrome(si, ei) && is_akaraka_palindrome(si, si + size / 2 - 1);
}

int main() {
  fast_io();

  cin >> s;
  cout << (is_akaraka_palindrome(0, s.size() - 1) ? "AKARAKA" : "IPSELENTI") << '\n';
}
