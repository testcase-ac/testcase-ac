#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = (1LL << 31);

void solve() {
  int N, M, K; cin >> N >> M >> K;
  vector<pii> A(K);
  for (int i = 0; i < K; i++) {
    int v, c; cin >> v >> c;
    A[i] = {v, c};
  }

  ll l = 1, r = INF;
  while (l < r) {
    ll m = (l + r) / 2;

    vector<int> S;
    for (int i = 0; i < K; i++) {
      auto [v, c] = A[i];
      if (c <= m) S.push_back(v);
    }
    sort(S.begin(), S.end(), greater<int>());

    ll sum = 0;
    if (S.size() >= N) for (int i = 0; i < N; i++) sum += S[i];

    if (sum >= M) r = m;
    else l = m + 1;
  }

  if (l == INF) cout << "-1\n";
  else cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
