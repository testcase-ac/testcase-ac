#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 3000;
int A[MAX], R[MAX], indegree[MAX + 1];
vector<int> adj[MAX + 1];

void solve() {
  int N, K, Q; cin >> N >> K >> Q;
  for (int i = 0; i < N; i++) cin >> A[i];

  for (int l = 0; l < N; l++) {
    int left = l, right = N;
    while (left < right) {
      int mid = (left + right) / 2;

      for (int i = 1; i <= K; i++) adj[i].clear();
      memset(indegree, 0, sizeof(indegree));

      int f = 1;
      for (int i = l; i < mid; i++) {
        int u = A[i], v = A[i + 1];
        if (f) adj[u].push_back(v), indegree[v]++;
        else adj[v].push_back(u), indegree[u]++;
        f = 1 - f;
      }

      queue<int> q;
      for (int i = 1; i <= K; i++) if (!indegree[i]) q.push(i);

      // Check if cycle
      int cnt = 0;
      while (!q.empty()) {
        int u = q.front(); q.pop();
        cnt++;
        for (int v : adj[u]) if (!--indegree[v]) q.push(v);
      }

      if (cnt == K) left = mid + 1;
      else right = mid;
    }
    R[l] = left - 1;
  }

  while (Q--) {
    int l, r; cin >> l >> r; l--; r--;
    if (R[l] >= r) cout << "YES\n";
    else cout << "NO\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
