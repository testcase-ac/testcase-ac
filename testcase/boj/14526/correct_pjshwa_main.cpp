#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX];
int S[MAX + 1], E[MAX + 1], C[MAX + 1];
int indegree[MAX + 1];
vector<int> adj[MAX + 1];

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];

  for (int i = 0; i < N; ++i) E[A[i]] = i;
  for (int i = N - 1; i >= 0; --i) S[A[i]] = i;

  stack<int> st;
  for (int i = 0; i < N; ++i) {
    int x = A[i];
    if (x == 0) {
      while (!st.empty()) st.pop();
      continue;
    }

    if (S[x] == i) {
      st.push(x);
    }

    if (st.top() != x) {
      cout << "-1\n";
      return;
    }

    if (E[x] == i) {
      st.pop();
      if (!st.empty()) {
        int y = st.top();
        adj[y].push_back(x);
        indegree[x]++;
      }
    }
  }

  queue<pii> q;
  for (int i = 1; i <= N; ++i) {
    if (indegree[i] == 0) q.emplace(i, 1);
  }

  int ans = 0;
  while (!q.empty()) {
    auto [x, d] = q.front(); q.pop();
    ans = max(ans, d);
    for (int y : adj[x]) {
      indegree[y]--;
      if (indegree[y] == 0) q.emplace(y, d + 1);
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
