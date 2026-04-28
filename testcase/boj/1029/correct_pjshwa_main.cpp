#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 15;
char table[MAX + 1][MAX + 1];
bool d[1 << MAX][MAX][10];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> table[i];

  d[1][0][0] = 1;
  int ans = 0;
  for (int state = 1; state < (1 << N); state++) {
    for (int prv = 0; prv < N; prv++) for (int nxt = 0; nxt < N; nxt++) {
      if (!(state & (1 << prv))) continue;
      if (state & (1 << nxt)) continue;

      int cost = table[prv][nxt] - '0';
      for (int ppr = 0; ppr <= cost; ppr++) {
        d[state ^ (1 << nxt)][nxt][cost] |= d[state][prv][ppr];
      }
    }

    int cnt = __builtin_popcount(state);
    for (int prv = 0; prv < N; prv++) for (int ppr = 0; ppr < 10; ppr++) {
      if (d[state][prv][ppr]) ans = max(ans, cnt);
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
