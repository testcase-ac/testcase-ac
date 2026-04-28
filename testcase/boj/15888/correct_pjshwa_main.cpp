#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int A, B, C;
  cin >> A >> B >> C;
  
  if (C % A || B % A) return cout << "둘다틀렸근\n", void();
  C /= A; B /= A;

  for (int x : {2, 4, 8, 16, 32, 64}) {
    int y = -B - x;
    if (x != y && x * y == C && y > 1 && (y & (y - 1)) == 0) {
      cout << "이수근\n";
      return;
    }
  }

  for (int x = -100; x <= 100; x++) {
    int y = -B - x;
    if (x != y && x * y == C) return cout << "정수근\n", void();
  }

  cout << "둘다틀렸근\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
