#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
double P[MAXN];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, K; double U; cin >> N >> K >> U;
  for (int i = 0; i < N; ++i) cin >> P[i];

  double prob = 0;
  for (int s = 0; s < (1 << N); ++s) {
    int cnt = __builtin_popcount(s);

    double cur = 1;
    for (int i = 0; i < N; ++i) {
      if (s & (1 << i)) cur *= P[i];
      else cur *= 1 - P[i];
    }
    if (cnt >= K) prob += cur;
  }

  cout << fixed << setprecision(10) << prob << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
