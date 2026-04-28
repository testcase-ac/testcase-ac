#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 26;
vector<int> adj[MAXN], R;
int N, M, I[MAXN];

int check() {
  vector<int> indeg(I, I + N);
  R.clear();
  queue<int> Q;

  for (int i = 0; i < N; ++i) {
    if (indeg[i] == 0) Q.push(i);
  }

  int unique = 1;
  for (int step = 0; step < N; ++step) {
    if (Q.empty()) return -1;
    if (Q.size() > 1) unique = 0;

    int u = Q.front(); Q.pop();
    R.push_back(u);

    for (int v : adj[u]) {
      if (--indeg[v] == 0) Q.push(v);
    }
  }
  return unique;
}

void solve() {
  for (int i = 0; i < N; ++i) {
    adj[i].clear();
    I[i] = 0;
  }

  vector<pii> edges;
  for (int i = 0; i < M; ++i) {
    string S; cin >> S;
    int u = S[0] - 'A', v = S[2] - 'A';
    edges.push_back({u, v});
  }

  for (int t = 1; t <= M; ++t) {
    auto [u, v] = edges[t - 1];
    adj[u].push_back(v); ++I[v];

    int res = check();
    if (res == 1) {
      cout << "Sorted sequence determined after " << t << " relations: ";
      for (int x : R) cout << char(x + 'A');
      cout << ".\n";
      return;
    } else if (res == -1) {
      cout << "Inconsistency found after " << t << " relations.\n";
      return;
    }
  }

  cout << "Sorted sequence cannot be determined.\n";
}

int main() {
  fast_io();

  while (cin >> N >> M) {
    if (N == 0 && M == 0) break;
    solve();
  }
}
