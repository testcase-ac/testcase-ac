#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  if (380 <= N && N < 425) cout << "Violet\n";
  else if (425 <= N && N < 450) cout << "Indigo\n";
  else if (450 <= N && N < 495) cout << "Blue\n";
  else if (495 <= N && N < 570) cout << "Green\n";
  else if (570 <= N && N < 590) cout << "Yellow\n";
  else if (590 <= N && N < 620) cout << "Orange\n";
  else cout << "Red\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
