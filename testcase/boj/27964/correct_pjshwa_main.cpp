#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool ends_with(string s, string t) {
  if (s.size() < t.size()) return false;
  for (int i = 0; i < t.size(); ++i) {
    if (s[s.size() - 1 - i] != t[t.size() - 1 - i]) return false;
  }
  return true;
}

void solve() {
  int N; cin >> N;

  set<string> U;
  for (int i = 0; i < N; ++i) {
    string s; cin >> s;
    if (ends_with(s, "Cheese")) U.insert(s);
  }

  if (U.size() >= 4) cout << "yummy\n";
  else cout << "sad\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
