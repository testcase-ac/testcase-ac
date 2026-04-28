#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200, INF = 0x3f3f3f3f;
vector<int> B[MAXN + 1], adj[MAXN + 1];
int P[MAXN + 1];

// returns true if B[i] contains B[j]
bool contains(int i, int j) {
  if (B[i].size() < B[j].size()) return false;
  vector<int> A = B[i], C = B[j];
  sort(A.begin(), A.end());
  sort(C.begin(), C.end());
  return includes(A.begin(), A.end(), C.begin(), C.end());
}

ll dfs(int v) {
  ll ret = P[v], acc = 0, sz = 0;
  for (int u : adj[v]) {
    acc += dfs(u);
    sz += B[u].size();
  }
  if (sz == B[v].size()) ret = min(ret, acc);
  return ret;
}

void solve() {
  int n, m; cin >> n >> m;

  memset(P, 0, sizeof(P));
  for (int i = 0; i <= MAXN; ++i) {
    B[i].clear();
    adj[i].clear();
  }

  P[0] = INF;
  for (int i = 1; i <= n; ++i) B[0].push_back(i);

  for (int i = 1; i <= m; ++i) {
    int si, x; cin >> P[i] >> si;
    while (si--) cin >> x, B[i].push_back(x);
    sort(B[i].begin(), B[i].end());
  }

  map<vector<int>, int> by_e;
  for (int i = 0; i <= m; ++i) {
    if (by_e.count(B[i])) by_e[B[i]] = min(by_e[B[i]], P[i]);
    else by_e[B[i]] = P[i];
  }

  vector<pair<vector<int>, int>> A;
  for (auto [v, p] : by_e) A.push_back({v, p});
  sort(A.begin(), A.end(), [&](auto& a, auto& b) {
    return a.first.size() < b.first.size();
  });

  m = 0;
  for (auto [v, p] : A) B[m] = v, P[m] = p, ++m;

  for (int i = 0; i < m; ++i) for (int j = i + 1; j < m; ++j) {
    if (contains(j, i)) {
      adj[j].push_back(i);
      break;
    }
  }

  assert(m > 0 && B[m - 1].size() == n);
  cout << dfs(m - 1) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
