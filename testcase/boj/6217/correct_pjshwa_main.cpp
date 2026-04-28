#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
int dt[MAX + 1];

void solve() {
  int N, I, H, R; cin >> N >> I >> H >> R;

  set<pii> S;
  while (R--) {
    int l, r; cin >> l >> r;
    if (l > r) swap(l, r);
    S.insert({l, r});
  }
  for (auto [l, r] : S) dt[l + 1]--, dt[r]++;

  int run = H;
  for (int i = 1; i <= N; i++) {
    run += dt[i];
    cout << run << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
