#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1 << 11;
int A[MAX];

bool is_power_of_two(int x) {
  return x && !(x & (x - 1));
}

// i: node
// j: 0: both, 1: left only, 2: right only
// k: 0: Azber's turn, 1: Biou's turn
ll d[MAX][3][2];

ll r(int i, int j, int k) {
  if (d[i][j][k] != -1) return d[i][j][k];
  if (i == 1) return d[i][j][k] = A[i];

  // Up
  ll ret = A[i];
  
  if (k) ret = max(ret, r(i / 2, 0, 1 - k) + A[i]);
  else ret = min(ret, r(i / 2, 0, 1 - k) + A[i]);

  // Left
  if (k) {
    if (!is_power_of_two(i) && j != 2) ret = max(ret, r(i - 1, 1, 1 - k) + A[i]);
  }
  else {
    if (!is_power_of_two(i) && j != 2) ret = min(ret, r(i - 1, 1, 1 - k) + A[i]);
  }

  // Right
  if (k) {
    if (!is_power_of_two(i + 1) && j != 1) ret = max(ret, r(i + 1, 2, 1 - k) + A[i]);
  }
  else {
    if (!is_power_of_two(i + 1) && j != 1) ret = min(ret, r(i + 1, 2, 1 - k) + A[i]);
  }

  return d[i][j][k] = ret;
}

void solve() {
  int N; cin >> N;
  for (int i = 1; i < (1 << N); i++) cin >> A[i];

  memset(d, -1, sizeof(d));
  for (int i = 1; i < (1 << N); i++) cout << r(i, 0, 0) << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
