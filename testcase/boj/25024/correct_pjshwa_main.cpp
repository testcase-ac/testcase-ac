#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int month[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

void solve() {
  int x, y;
  cin >> x >> y;

  if (0 <= x && x <= 23 && 0 <= y && y <= 59) cout << "Yes";
  else cout << "No";

  cout << ' ';

  if (1 <= x && x <= 12) {
    if (1 <= y && y <= month[x]) cout << "Yes";
    else cout << "No";
  }
  else cout << "No";

  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
