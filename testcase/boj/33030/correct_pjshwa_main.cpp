#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e5;
vector<int> adj[MAXN + 10];
vector<pii> O;
int N, M, indegree[MAXN + 10], ops[MAXN + 10], C[4];

// 0 ... 0 1 2 ... 2 3 0 ... 0
void solve_mu2() {
  if (C[1] != 1 || C[3] != 1) return cout << "-1\n", void();
  for (auto& [a, b] : O) {
    if (ops[a] > ops[b] && ops[b] != 0) return cout << "-1\n", void();
  }

  for (auto& [a, b] : O) {
    if (ops[a] == ops[b]) {
      adj[a].push_back(b); ++indegree[b];
    } else if (ops[a] == 0) {
      adj[a].push_back(N); ++indegree[N];
    } else if (ops[b] == 0) {
      adj[N].push_back(b); ++indegree[b];
    }
  }

  queue<int> Q0, Q2;
  for (int i = 0; i <= N; ++i) {
    if (indegree[i] > 0) continue;
    if (ops[i] == 0) Q0.push(i);
    else if (ops[i] == 2) Q2.push(i);
  }

  vector<int> V0, V2;
  while (!Q0.empty()) {
    int t = Q0.front(); Q0.pop();
    V0.push_back(t);
    for (int nxt : adj[t]) {
      if (--indegree[nxt] == 0) Q0.push(nxt);
    }
  }
  while (!Q2.empty()) {
    int t = Q2.front(); Q2.pop();
    V2.push_back(t);
    for (int nxt : adj[t]) {
      if (--indegree[nxt] == 0) Q2.push(nxt);
    }
  }

  vector<int> ans;
  for (int v : V0) {
    if (v != N) ans.push_back(v);
    else {
      for (int i = 0; i < N; ++i) if (ops[i] == 1) ans.push_back(i);
      for (int v : V2) ans.push_back(v);
      for (int i = 0; i < N; ++i) if (ops[i] == 3) ans.push_back(i);
    }
  }

  if ((int)ans.size() != N) return cout << "-1\n", void();
  for (int v : ans) cout << v + 1 << ' ';
  cout << '\n';
}

// 0 ... 0 1 2 ... 2
void solve_mu1() {
  if (C[1] != 1) return cout << "-1\n", void();
  for (auto& [a, b] : O) {
    if (ops[a] > ops[b]) return cout << "-1\n", void();
  }

  for (auto& [a, b] : O) {
    if (ops[a] == ops[b]) {
      adj[a].push_back(b); ++indegree[b];
    }
  }

  queue<int> Q0, Q2;
  for (int i = 0; i < N; ++i) {
    if (indegree[i] > 0) continue;
    if (ops[i] == 0) Q0.push(i);
    else if (ops[i] == 2) Q2.push(i);
  }

  vector<int> V0, V2;
  while (!Q0.empty()) {
    int t = Q0.front(); Q0.pop();
    V0.push_back(t);
    for (int nxt : adj[t]) {
      if (--indegree[nxt] == 0) Q0.push(nxt);
    }
  }
  while (!Q2.empty()) {
    int t = Q2.front(); Q2.pop();
    V2.push_back(t);
    for (int nxt : adj[t]) {
      if (--indegree[nxt] == 0) Q2.push(nxt);
    }
  }

  vector<int> ans;
  for (int v : V0) ans.push_back(v);
  for (int i = 0; i < N; ++i) if (ops[i] == 1) ans.push_back(i);
  for (int v : V2) ans.push_back(v);

  if ((int)ans.size() != N) return cout << "-1\n", void();
  for (int v : ans) cout << v + 1 << ' ';
  cout << '\n';
}

// 0 ... 0
void solve_mu0() {
  if (C[2] != 0) return cout << "-1\n", void();

  for (auto& [a, b] : O) {
    if (ops[a] == ops[b]) {
      adj[a].push_back(b); ++indegree[b];
    }
  }

  queue<int> Q0;
  for (int i = 0; i < N; ++i) {
    if (indegree[i] > 0) continue;
    if (ops[i] == 0) Q0.push(i);
  }

  vector<int> V0;
  while (!Q0.empty()) {
    int t = Q0.front(); Q0.pop();
    V0.push_back(t);
    for (int nxt : adj[t]) {
      if (--indegree[nxt] == 0) Q0.push(nxt);
    }
  }

  vector<int> ans;
  for (int v : V0) ans.push_back(v);

  if ((int)ans.size() != N) return cout << "-1\n", void();
  for (int v : ans) cout << v + 1 << ' ';
  cout << '\n';
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) {
    string t, r; cin >> t >> r;
    int op = 0;
    if (t == "unset" && r == "false") op = 0;
    if (t == "unset" && r == "true") op = 3;
    if (t == "set" && r == "false") op = 2;
    if (t == "set" && r == "true") op = 1;
    ops[i] = op; ++C[op];
  }

  cin >> M; O.resize(M);
  for (auto& [a, b] : O) cin >> a >> b, --a, --b;

  int mu = C[1] + C[3];
  if (mu == 2) solve_mu2();
  else if (mu == 1) solve_mu1();
  else solve_mu0();
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
