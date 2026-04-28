#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll N, P, H; cin >> N >> P >> H;
  vector<int> F(N); ll o = H;
  for (int i = N - 1; i >= 0; --i) {
    ll w = 1LL << i;
    if (o > w) {
      F[i] = 1;
      o = 2 * w + 1 - o;
    }
  }

  ll L = 1LL << N, TH = 1; o = 1;
  auto flip = [&](int d) {
    cout << (d ? 'L' : 'R');
    if ((P > L / 2) ^ d) {
      o = 2 * TH + 1 - o;
      P = L + 1 - P;
    }
    if (d) P -= L / 2;
    L /= 2; TH *= 2;
  };

  for (int i = 0; i < N; ++i) {
    flip(F[i] ? (P <= L / 2) : (P > L / 2));
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
