#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;
  
  map<string, int> t;
  for (int i = 0; i < N; i++) {
    string o; int x;
    cin >> o >> x;
    t[o] += x;
  }

  for (auto& [k, v] : t) {
    if (v == 5) return cout << "YES\n", void();
  }
  cout << "NO\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
