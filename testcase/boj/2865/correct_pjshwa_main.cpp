#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N, M, K;
  cin >> N >> M >> K;

  double by_player[N][M];
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < N; j++) {
      int p; cin >> p;
      cin >> by_player[p - 1][i];
    }
  }

  vector<double> powers;
  for (int i = 0; i < N; i++) {
    double pow = 0;
    for (int j = 0; j < M; j++) pow = max(pow, by_player[i][j]);
    powers.push_back(pow);
  }
  sort(powers.begin(), powers.end(), greater<double>());

  double ans = 0;
  for (int i = 0; i < K; i++) ans += powers[i];
  cout << fixed << setprecision(1) << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
