#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  int c3 = -1, c5 = -1;
  for (int i = 0; i < 8; i++) {
    int v = 3 * i;
    if (v > n || (n - v) % 8) continue;
    c3 = i;
  }
  for (int i = 0; i < 8; i++) {
    int v = 5 * i;
    if (v > n || (n - v) % 8) continue;
    c5 = i;
  }

  if (c3 == -1 && c5 == -1) cout << "-1";
  else if (c3 == -1) {
    for (int i = 0; i < c5; i++) cout << '5';
    for (int i = 0; i < (n - 5 * c5) / 8; i++) cout << '8';
  }
  else if (c5 == -1) {
    for (int i = 0; i < c3; i++) cout << '3';
    for (int i = 0; i < (n - 3 * c3) / 8; i++) cout << '8';
  }
  else {
    if (c3 + (n - 3 * c3) / 8 <= c5 + (n - 5 * c5) / 8) {
      for (int i = 0; i < c3; i++) cout << '3';
      for (int i = 0; i < (n - 3 * c3) / 8; i++) cout << '8';
    }
    else {
      for (int i = 0; i < c5; i++) cout << '5';
      for (int i = 0; i < (n - 5 * c5) / 8; i++) cout << '8';
    }
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
