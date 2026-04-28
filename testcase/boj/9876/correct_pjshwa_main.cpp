#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 100;
int PR[MAX + 1][MAX + 1], PS[MAX + 1][MAX + 1];
char board[MAX + 1][MAX + 1];
bool vis[MAX + 1][MAX + 1], L[MAX + 1][MAX + 1];
int N, M;

bool check(int p) {
  queue<pii> q;
  memset(vis, false, sizeof(vis));
  memset(L, false, sizeof(L));
  for (int i = 1; i <= N; i++) for (int j = 1; j <= M; j++) {
    int rsz = 0, ssz = 0;
    for (int k = 0; k < p; k++) for (int l = 0; l < p; l++) {
      if (board[i + k][j + l] == 'R') rsz++;
      if (board[i + k][j + l] == 'S') ssz++;
    }
    if (rsz == p * p || ssz == p * p) {
      vis[i][j] = true;
      q.push({i, j});
    }
  }

  while (!q.empty()) {
    auto [i, j] = q.front(); q.pop();
    for (int k = 0; k < p; k++) for (int l = 0; l < p; l++) L[i + k][j + l] = true;
    
  }

}

void solve() {
  cin >> N >> M;
  for (int i = 1; i <= N; i++) {
    string S; cin >> S;
    for (int j = 1; j <= M; j++) board[i][j] = S[j - 1];
  }

  int left = 1, right = min(N, M) + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (check(mid)) left = mid + 1;
    else right = mid;
  }
  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
