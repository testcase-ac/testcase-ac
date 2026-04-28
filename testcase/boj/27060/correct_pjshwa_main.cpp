#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int V[26];
void solve() {
  string S;
  while (cin >> S) {
    for (char c : S) if (c >= 'A' && c <= 'Z') ++V[c - 'A'];
  }

  int vmax = *max_element(V, V + 26);
  for (int r = vmax; r >= 1; --r) {
    string row;
    for (int i = 0; i < 26; ++i) {
      if (V[i] >= r) row += '*';
      else row += ' ';
      if (i < 25) row += ' ';
    }
    while (row.back() == ' ') row.pop_back();
    cout << row << '\n';
  }

  for (int i = 0; i < 26; ++i) {
    cout << (char)('A' + i);
    if (i < 25) cout << ' ';
    else cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
