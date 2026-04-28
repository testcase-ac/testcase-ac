#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int X, Y; cin >> X >> Y;
  for (int i = 0; i < X; i++) cout << "WE";
  for (int i = 0; i < -X; i++) cout << "EW";
  for (int i = 0; i < Y; i++) cout << "SN";
  for (int i = 0; i < -Y; i++) cout << "NS";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
