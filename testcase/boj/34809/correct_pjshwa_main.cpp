#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MOD = 1e6 + 3;
int Pinv[MOD];

void solve() {
  vector<int> P;
  for (int i = 0; i < MOD; ++i) P.push_back(1LL * i * i % MOD);

  memset(Pinv, -1, sizeof(Pinv));
  for (int i = 0; i < MOD; ++i) Pinv[P[i]] = i;

  cout << MOD << '\n';
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int x; cin >> x;
    for (int p1 = 0; p1 < MOD; ++p1) {
      if (Pinv[p1] == -1) continue;
      int p2 = (x - p1 + MOD) % MOD;
      if (Pinv[p2] == -1) continue;
      cout << Pinv[p1] << ' ' << Pinv[p2] << '\n';
      break;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
