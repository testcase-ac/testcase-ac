#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1000;
ll C[MAXN];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) {
    int k, ti; cin >> k;
    while (k--) {
      cin >> ti; --ti;
      C[i] |= 1LL << ti;
    }
  }

  int M; cin >> M;
  while (M--) {
    int p, qi; cin >> p;
    ll v = 0;
    while (p--) {
      cin >> qi; --qi;
      v |= 1LL << qi;
    }
    int cnt = 0;
    for (int i = 0; i < N; ++i) {
      if ((C[i] & v) == C[i]) ++cnt;
    }
    cout << cnt << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
