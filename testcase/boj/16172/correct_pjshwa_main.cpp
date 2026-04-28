#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string X, T, S; cin >> X >> T;
  for (char& c : X) if (!isdigit(c)) S += c;
  cout << (S.find(T) != string::npos) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
