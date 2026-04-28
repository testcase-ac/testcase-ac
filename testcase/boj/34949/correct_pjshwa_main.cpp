#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<int> adj[MAXN + 1];
int cdist[MAXN + 1];

void solve() {
  int N; cin >> N;
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    adj[x].push_back(i);
  }

  memset(cdist, -1, sizeof(cdist));
  queue<int> q;
  cdist[N] = 0; q.push(N);
  while (!q.empty()) {
    int cur = q.front(); q.pop();
    for (int nxt : adj[cur]) {
      if (cdist[nxt] == -1) {
        cdist[nxt] = cdist[cur] + 1;
        q.push(nxt);
      }
    }
  }

  for (int i = 1; i <= N; ++i) cout << cdist[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
