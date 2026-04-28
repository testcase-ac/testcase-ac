#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

char tolower(char c) {
  if ('A' <= c && c <= 'Z') return c - 'A' + 'a';
  return c;
}

void solve() {
  string A, S; cin >> A;

  vector<char> B;
  while (cin >> S) B.push_back(S[0]);

  for (char a : A) {
    bool ok = false;
    for (char b : B) ok |= a == b;
    if (ok) a = tolower(a);
    cout << a;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
