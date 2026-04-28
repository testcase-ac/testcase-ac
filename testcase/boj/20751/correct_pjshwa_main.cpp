#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, R, C, S; cin >> N >> M >> R >> C >> S;

  bool rfill = R - S <= 1 && R + S >= N;
  bool cfill = C - S <= 1 && C + S >= M;
  bool zfill1 = R - S <= 1 && C - S <= 1;
  bool zfill2 = R + S >= N && C + S >= M;
  if (rfill || cfill || zfill1 || zfill2) cout << "Tuzik\n";
  else cout << "Barsik\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
