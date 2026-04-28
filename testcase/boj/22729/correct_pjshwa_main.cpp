#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 50;
char board[MAXN + 1][MAXN + 1];
int Xmin[26], Xmax[26], Ymin[26], Ymax[26], cnts[26];
int O[MAXN][MAXN], V[26];

bool E(int c) {
  if (cnts[c] == 0) return false;
  return cnts[c] == (Xmax[c] - Xmin[c] + 1) * (Ymax[c] - Ymin[c] + 1);
}

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N; ++i) cin >> board[i];

  memset(cnts, 0, sizeof(cnts));
  memset(O, 0, sizeof(O)); memset(V, 0, sizeof(V));
  for (int i = 0; i < N; ++i) for (int j = 0; j < M; ++j) {
    if (board[i][j] == '.') continue;

    int c = board[i][j] - 'A';
    if (cnts[c] == 0) {
      Xmin[c] = Xmax[c] = i;
      Ymin[c] = Ymax[c] = j;
    } else {
      Xmin[c] = min(Xmin[c], i); Xmax[c] = max(Xmax[c], i);
      Ymin[c] = min(Ymin[c], j); Ymax[c] = max(Ymax[c], j);
    }
    ++cnts[c];
  }

  queue<int> Q;
  for (int u = 0; u < 26; ++u) if (E(u)) Q.push(u), V[u] = 1;

  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    for (int i = Xmin[u]; i <= Xmax[u]; ++i) for (int j = Ymin[u]; j <= Ymax[u]; ++j) {
      if (O[i][j]) continue;
      O[i][j] = 1;
      for (int v = 0; v < 26; ++v) {
        if (cnts[v] == 0) continue;
        if (Xmin[v] > i || Xmax[v] < i || Ymin[v] > j || Ymax[v] < j) continue;
        ++cnts[v];
      }
    }
    for (int v = 0; v < 26; ++v) if (!V[v] && E(v)) Q.push(v), V[v] = 1;
  }

  for (int u = 0; u < 26; ++u) {
    if (cnts[u] && !V[u]) return cout << "SUSPICIOUS\n", void();
  }
  cout << "SAFE\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
