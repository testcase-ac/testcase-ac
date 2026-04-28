#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
ll A[MAXN];

void solve() {
  ll N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> A[i];

  while (1) {
    ll acc = 0;
    for (int i = 0; i < N; ++i) {
      if (acc + A[i] <= M) acc += A[i];
    }
    if (acc == 0) break;
    M %= acc;
  }
  cout << M << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
