#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; string S; cin >> N >> S;

  map<char, int> tal;
  for (char c : S) tal[c]++;

  int U = 0;
  for (char c : {'r', 'o', 'y', 'g', 'b', 'i', 'v'}) {
    if (tal[c] == 0) U |= 1;
  }
  for (char c : {'R', 'O', 'Y', 'G', 'B', 'I', 'V'}) {
    if (tal[c] == 0) U |= 2;
  }

  if (U == 0) cout << "YeS\n";
  if (U == 1) cout << "YES\n";
  if (U == 2) cout << "yes\n";
  if (U == 3) cout << "NO!\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
