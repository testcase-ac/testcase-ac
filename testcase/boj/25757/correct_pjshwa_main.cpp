#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string T;
  cin >> N >> T;

  int div;
  if (T == "Y") div = 1;
  if (T == "F") div = 2;
  if (T == "O") div = 3;

  set<string> u;
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    u.insert(s);
  }

  cout << (u.size() / div) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
