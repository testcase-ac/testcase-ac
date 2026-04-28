#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int C[6][13] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
  {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1},
  {1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1},
  {1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1},
  {1, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1},
  {1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1},
};
const int T[6] = {11, 9, 9, 9, 8, 8};

void solve() {
  int N, x, sum = 0; cin >> N;
  if (N == 10) x = 5;
  else if (N >= 5) x = 4;
  else x = N - 1;

  cout << T[x] << '\n';
  for (int j = 0; j < 13; ++j) {
    if (C[x][j] == 0) continue;
    cout << (char)('A' + j) << ' ';
    ++sum;
  }
  cout << '\n';
  assert(sum == T[x]);
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
