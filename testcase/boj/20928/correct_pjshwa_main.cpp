#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, INF = 1e9 + 7;
int P[MAX + 1];

void solve() {
  int N, M;
  cin >> N >> M;

  vector<pii> a(N);
  for (int i = 0; i < N; i++) cin >> a[i].first;
  for (int i = 0; i < N; i++) cin >> a[i].second;

  fill(P, P + M + 1, INF);
  P[a[0].first] = 0;
  int j = a[0].first + 1;

  for (int i = 0; i < N; i++) {
    auto [cp, cx] = a[i];
    if (P[cp] == INF) break;

    while (j <= M && j <= cp + cx) {
      P[j] = i == 0 ? 0 : P[cp] + 1;
      j++;
    }
  }

  if (P[M] == INF) cout << "-1\n";
  else cout << P[M] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
