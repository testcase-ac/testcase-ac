#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1}, dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};
bool in_range(int qx, int qy, int kx, int ky) {
  if (qx - qy == kx - ky) return true;
  if (qx + qy == kx + ky) return true;
  if (qx == kx) return true;
  if (qy == ky) return true;
  return false;
}

void solve() {
  int N, K, R, C;
  cin >> N >> K >> R >> C;

  vector<pii> queens(K);
  for (auto& [x, y] : queens) cin >> x >> y;

  int tota = 0, cent = 0;
  for (auto& [x, y] : queens) {
    cent |= in_range(x, y, R, C);
  }
  for (int k = 0; k < 8; k++) {
    int cur = 0;
    int nx = R + dx[k], ny = C + dy[k];
    if (nx < 1 || nx > N || ny < 1 || ny > N) {
      tota++;
      continue;
    }

    for (auto& [x, y] : queens) {
      cur |= in_range(x, y, R + dx[k], C + dy[k]);
    }
    tota += cur;
  }

  if (cent) {
    if (tota == 8) cout << "CHECKMATE\n";
    else cout << "CHECK\n";
  }
  else if (tota == 8) cout << "STALEMATE\n";
  else cout << "NONE\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
