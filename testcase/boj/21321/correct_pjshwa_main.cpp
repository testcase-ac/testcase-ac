#include <bits/stdc++.h> 
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 16, INF = 0x3f3f3f3f;
int a[MAX], b[MAX];
int d[1 << MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i] >> b[i];
  for (int i = 0; i < (1 << N); i++) d[i] = -INF;

  d[0] = 0;
  for (int state = 1; state < (1 << N); state++) {
    int round = __builtin_popcount(state);

    for (int nxt = 0; nxt < N; nxt++) {
      if (!(state & (1 << nxt))) continue;

      bool able = true;
      for (int prv = 0; prv < nxt; prv++) {
        if (a[nxt] % a[prv]) continue;
        if (state & (1 << prv)) continue;
        able = false;
        break;
      }
      if (!able) continue;

      d[state] = max(
        d[state],
        d[state ^ (1 << nxt)] + (b[nxt] * round)
      );
    }
  }

  cout << d[(1 << N) - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
