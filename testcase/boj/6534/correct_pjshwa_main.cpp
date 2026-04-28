#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj[MAXN + 1];
int indegree[MAXN + 1], indegree_o[MAXN + 1], N1, N2, N, D;

bool is_disc(int n, int d) {
  if (d == 1) return n <= N1;
  else return n > N1;
}

int do_disc(int d) {
  deque<int> dq;
  copy(indegree_o, indegree_o + N + 1, indegree);
  for (int i = 1; i <= N; ++i) {
    if (indegree[i] > 0) continue;
    if (is_disc(i, d)) dq.push_front(i);
    else dq.push_back(i);
  }

  int last = d, ans = 2;
  while (!dq.empty()) {
    int u = dq.front(); dq.pop_front();
    if (!is_disc(u, last)) {
      last = 3 - last;
      ++ans;
    }
    for (int v : adj[u]) {
      if (--indegree[v] > 0) continue;
      if (is_disc(v, last)) dq.push_front(v);
      else dq.push_back(v);
    }
  }
  return ans;
}

void solve() {
  N = N1 + N2;
  for (int i = 1; i <= N; ++i) {
    adj[i].clear();
    indegree[i] = indegree_o[i] = 0;
  }

  while (D--) {
    int u, v; cin >> u >> v;
    adj[v].push_back(u);
    ++indegree_o[u];
  }

  cout << min(do_disc(1), do_disc(2)) << '\n';
}

int main() {
  fast_io();

  while (cin >> N1 >> N2 >> D) {
    if (N1 == 0 && N2 == 0 && D == 0) break;
    solve();
  }
}
