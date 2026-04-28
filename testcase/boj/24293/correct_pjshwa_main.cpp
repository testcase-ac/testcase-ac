#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  while (S.size() > 2) {
    string ns = "";
    for (int i = 1; i <= S.size(); i++) {
      if (i % 3 == 0) continue;
      ns += S[i - 1];
    }
    
    reverse(ns.begin(), ns.end());
    S = ns;
  }

  sort(S.begin(), S.end());
  cout << S << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
