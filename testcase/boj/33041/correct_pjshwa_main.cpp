#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
ll W[MAXN + 1], S[MAXN + 1], Dc[MAXN + 1];

void solve() {
  int H, C, D; cin >> H;
  for (int i = 1; i <= H; ++i) cin >> W[i];
  cin >> C >> D;

  ll Dtot = 0;
  for (int i = 1; i <= H; ++i) {
    S[i] = W[i];
    if (i == 1) continue;

    ll dif = S[i - 1] - S[i];
    if (dif < 0) continue;

    ll add = (dif + 8) / 8;
    Dc[i] += add; Dtot += add;
    S[i] += add * 8;
  }
  for (int i = 1; i <= H; ++i) {
    if (Dtot > D || Dc[i] > W[i]) return cout << "-1\n", void();
  }
  D -= Dtot;

  while (D && Dc[H] < W[H]) {
    ++Dc[H]; --D; S[H] += 8;
  }
  for (int i = H - 1; i >= 1; --i) {
    while (D && Dc[i] < W[i] && S[i] + 8 < S[i + 1]) {
      ++Dc[i]; --D; S[i] += 8;
    }
  }
  if (D) return cout << "-1\n", void();

  for (int i = 1; i <= H; ++i) {
    ll t = W[i];
    while (t--) {
      if (Dc[i]) cout << "9 ", --Dc[i];
      else cout << "1 ";
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
