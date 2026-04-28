#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  string A = "", B = "";
  for (int i = 0; i < N; ++i) {
    string s; cin >> s; A += s;
  }
  for (int i = 0; i < N; ++i) {
    string s; cin >> s; B += s;
  }

  ll Al = stoll(A), Bl = stoll(B);
  cout << min(Al, Bl) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
