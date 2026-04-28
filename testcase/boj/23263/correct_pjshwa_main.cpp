#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 1e9 + 7;

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, K;
  cin >> N >> K;
  vector<ll> BL(N + 10, 0), BR(N + 10, 0);
  for (int i = 1; i <= N; i++) cin >> BL[i];
  for (int i = N; i >= 1; i--) BR[i] = BL[i];
  for (int i = 1; i <= N; i++) BL[i] += BL[i - 1];
  for (int i = N; i >= 1; i--) BR[i] += BR[i + 1];

  vector<int> rd(K + 1, INF);
  rd[0] = 0;

  int ans = INF;
  for (int e = N; e >= 1; e--) {
    for (int s = 1; s <= e; s++) {
      ll val = BL[e] - BL[s - 1];
      if (val > K) continue;
      ans = min(ans, rd[K - val] + e - s + 1);
    }

    for (int v = e; v <= N; v++) {
      ll val = BR[e] - BR[v + 1];
      if (val > K) continue;
      rd[val] = min(rd[val], v - e + 1);
    }
  }

  if (ans == INF) cout << "-1\n";
  else cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
