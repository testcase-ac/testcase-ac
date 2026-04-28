#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int N, J;
void solve() {
  queue<int> q;
  for (int i = 0, x; i < N; i++) {
    cin >> x;
    q.push(x);
  }

  int player = 0;
  int discard[14] = {0};
  int ptop[J + 1] = {0};
  int pcnt[J + 1] = {0};

  bool cplayer = false;
  while (1) {
    if (q.empty()) break;

    player++;
    if (player == J + 1) player = 1;

    // Player loop
    while (!q.empty()) {
      int c = q.front(); q.pop();
      if (discard[c]) {
        pcnt[player] += 2;
        ptop[player] = c;
        discard[c] = 0;
      }
      else {
        bool f = false;
        for (int o = 1; o <= J; o++) {
          if (o == player) continue;

          if (ptop[o] == c) {
            pcnt[player] += pcnt[o] + 1;
            ptop[player] = c;
            ptop[o] = pcnt[o] = 0;
            f = true;
          }
        }
        if (f) continue;

        if (ptop[player] == c) pcnt[player]++;
        else {
          discard[c]++;
          break;
        }
      }
    }
  }

  int mcards = 0;
  for (int i = 1; i <= J; i++) mcards = max(mcards, pcnt[i]);
  cout << mcards << ' ';

  for (int i = 1; i <= J; i++) {
    if (pcnt[i] == mcards) cout << i << ' ';
  }
  cout << '\n';
}

int main() {
  fast_io();

  while (cin >> N >> J) {
    if (N == 0 && J == 0) break;
    solve();
  }
}
