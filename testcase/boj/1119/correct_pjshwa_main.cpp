#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> board[i];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
