#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXC = 900;

void solve() {
  int N, M, K; cin >> N >> M >> K;

  vector<ll> D(N);
  for (int i = 0; i < N; i++) cin >> D[i];

  vector<pair<ll, ll>> A(K);
  for (int i = 0; i < K; i++) {
    ll P, Q; cin >> P >> Q;
    A[i] = {P, Q};
  }

  // 15 min = 900 sec
  priority_queue<ll> best;
  for (int i = 0; i < N; i++) {
    vector<pair<ll, ll>> B(K);
    for (int j = 0; j < K; j++) {
      auto [P, Q] = A[j];
      B[j] = {(P + D[i] - 1) / D[i], Q};
    }
    
    vector<ll> C(MAXC + 1, 0);
    for (auto [P, Q] : B) {
      for (int j = MAXC; j >= P; j--) {
        C[j] = max(C[j], C[j - P] + Q);
      }
    }

    best.push(C[MAXC]);
  }

  ll ans = 0;
  while (M--) {
    ans += best.top();
    best.pop();
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
