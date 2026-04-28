#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
    
  map<string, int> T;
  for (int i = 0; i < N; ++i) {
    string x; cin >> x;
    ++T[x];
  }
  string x; cin >> x;
  cout << T[x] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
