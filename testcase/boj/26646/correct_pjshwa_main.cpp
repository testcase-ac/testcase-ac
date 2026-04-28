#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll INF = 1e18;

void solve() {
  int N;
  cin >> N;

  vector<int> H(N);
  for (int i = 0; i < N; i++) cin >> H[i];

  vector<ll> D(101, INF), L(101);
  D[H[0]] = 0, L[H[0]] = H[0];

  int w = H[0];
  for (int i = 1; i < N; i++) {
    w += H[i] + H[i - 1];
    ll cur = INF;
    for (int v = 1; v <= 100; v++) {
      if (D[v] == INF) continue;

      ll wdif = w - L[v];
      ll cost = wdif * wdif + (v - H[i]) * (v - H[i]);
      cur = min(cur, D[v] + cost);
    }

    D[H[i]] = cur;
    L[H[i]] = w;
  }

  cout << D[H[N - 1]] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
