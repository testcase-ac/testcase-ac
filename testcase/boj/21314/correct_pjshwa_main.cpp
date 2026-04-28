#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  string S; cin >> S;

  int streak = 0;
  for (char& c : S) {
    if (c == 'M') streak++;
    else {
      cout << '5';
      for (int i = 0; i < streak; i++) cout << '0';
      streak = 0;
    }
  }
  for (int i = 0; i < streak; i++) cout << '1';
  cout << '\n';

  streak = 0;
  for (char& c : S) {
    if (c == 'M') streak++;
    else {
      if (streak) cout << '1';
      for (int i = 0; i < streak - 1; i++) cout << '0';
      streak = 0;
      cout << '5';
    }
  }
  if (streak) cout << '1';
  for (int i = 0; i < streak - 1; i++) cout << '0';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
