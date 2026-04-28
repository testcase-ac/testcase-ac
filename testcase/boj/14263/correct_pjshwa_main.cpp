#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 50;
char board[MAX + 1][MAX + 1];
int hl[128], hu[128], vl[128], vu[128], cnt[128];
int indegree[128];
bool adj[128][128];

void solve() {
  int N, M;
  cin >> N >> M;
  for (int i = 0; i < N; i++) cin >> board[i];

  memset(hl, -1, sizeof(hl));
  memset(hu, -1, sizeof(hu));
  memset(vl, -1, sizeof(vl));
  memset(vu, -1, sizeof(vu));

  for (int i = 0; i < N; i++) for (int j = 0; j < M; j++) {
    if (board[i][j] == '.') continue;

    int c = board[i][j];
    if (hl[c] == -1) {
      hl[c] = hu[c] = i;
      vl[c] = vu[c] = j;
    }
    else {
      hl[c] = min(hl[c], i);
      vl[c] = min(vl[c], j);
      hu[c] = max(hu[c], i);
      vu[c] = max(vu[c], j);
    }
    cnt[c]++;
  }

  queue<int> q;
  int z = 0;
  for (int b = 0; b < 128; b++) {
    if (cnt[b] == 0) continue;

    z++;
    for (int i = hl[b]; i <= hu[b]; i++) for (int j = vl[b]; j <= vu[b]; j++) {
      int v = board[i][j];
      if (v == '.') return cout << "-1\n", void();
      else if (v != b && !adj[b][v]) {
        adj[b][v] = true;
        indegree[v]++;
      }
    }
  }

  priority_queue<int, vector<int>, greater<int>> tq;
  for (int b = 0; b < 128; b++) {
    if (cnt[b] > 0 && indegree[b] == 0) tq.push(b);
  }

  vector<char> ans;
  for (int i = 1; i <= z; i++) {
    if (tq.empty()) return cout << "-1\n", void();

    int v = tq.top(); tq.pop();
    ans.push_back(v);
    for (int b = 0; b < 128; b++) {
      if (!adj[v][b]) continue;
      indegree[b]--;
      if (indegree[b] == 0) tq.push(b);
    }
  }

  for (char c : ans) cout << c;
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
