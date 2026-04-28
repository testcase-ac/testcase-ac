#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;
  map<string, int> t;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    t[s]++;
  }
  for (int i = 0; i < n - 1; i++) {
    string s;
    cin >> s;
    t[s]--;
  }
  for (auto [name, occ] : t) {
    if (occ) return cout << name << '\n', void();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
