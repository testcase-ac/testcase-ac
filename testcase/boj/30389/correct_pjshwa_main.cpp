#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  set<string> U;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;
    for (int j = 0; j < S.size(); ++j) {
      string T = S.substr(j);
      if (U.count(T)) U.erase(T);
      else U.insert(T);
    }
  }

  cout << U.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
