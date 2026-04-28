#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2e5;
vector<int> adj[MAXN + 1];
int indegree[MAXN + 1], parent[MAXN + 1], level[MAXN + 1];

using T = tuple<int, int, int>;

void dfs(int v, int l) {
  level[v] = l;
  for (int u : adj[v]) {
    parent[u] = v;
    dfs(u, l + 1);
  }
}

void solve() {
  int N; cin >> N;

  vector<T> circles;
  for (int i = 0; i < N; ++i) {
    int idx, x, r; cin >> idx >> x >> r;
    circles.emplace_back(x - r, 0, idx);
    circles.emplace_back(x + r, 1, idx);
  }
  sort(circles.begin(), circles.end());

  stack<T> S;
  for (T& c : circles) {
    auto [x, t, idx] = c;
    if (t == 0) {
      int pidx = 0;
      if (!S.empty()) pidx = get<2>(S.top());

      adj[pidx].push_back(idx);
      indegree[idx]++;
      S.push(c);
    }
    else S.pop();
  }

  dfs(0, 0);
  int A, B; cin >> A >> B;

  vector<int> traj_A, traj_B;
  while (level[A] > level[B]) {
    traj_A.push_back(A);
    A = parent[A];
  }
  while (level[A] < level[B]) {
    traj_B.push_back(B);
    B = parent[B];
  }
  while (A != B) {
    traj_A.push_back(A);
    traj_B.push_back(B);
    A = parent[A];
    B = parent[B];
  }
  traj_A.push_back(A);

  cout << traj_A.size() + traj_B.size() << "\n";
  for (int e : traj_A) cout << e << " ";
  while (!traj_B.empty()) {
    cout << traj_B.back() << " ";
    traj_B.pop_back();
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
