#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned int;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 12;
char board[MAX + 1][MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
