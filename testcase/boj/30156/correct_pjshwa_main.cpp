#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;
  int acnt = 0, bcnt = 0;
  for (char& c : S) {
    if (c == 'a') ++acnt;
    if (c == 'b') ++bcnt;
  }
  cout << min(acnt, bcnt) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
