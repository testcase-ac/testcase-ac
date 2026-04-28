#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& a) {
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
}

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

class SCC {
  int n, dfs_cnt;
  vector<vector<int>> adj;
  vector<int> dfs_order;
  stack<int> S;

  vector<int> scc_vis, scc_indegree;

  int dfs(int cur) {
    int ret = dfs_order[cur] = ++dfs_cnt; S.push(cur);
    for (const auto& nxt : adj[cur]) {
      if (!dfs_order[nxt]) ret = min(ret, dfs(nxt));
      else if (!scc[nxt]) ret = min(ret, dfs_order[nxt]);
    }
    if (ret == dfs_order[cur]) {
      for (scc_cnt++; S.size();) {
        int t = S.top(); S.pop();
        scc[t] = scc_cnt;
        if (t == cur) break;
      }
    }
    return ret;
  }

  void reconstruct() {
    scc_graph.resize(scc_cnt + 1);
    scc_vis.resize(scc_cnt + 1, 0);
    scc_indegree.resize(scc_cnt + 1, 0);

    for (int i = 1; i <= n; i++) {
      for (int j : adj[i]) {
        if (scc[i] == scc[j]) continue;
        scc_graph[scc[i]].push_back(scc[j]);
      }
    }

    for (int i = 1; i <= scc_cnt; i++) {
      compress(scc_graph[i]);
      for (int v : scc_graph[i]) scc_indegree[v]++;
    }
  }

public:
  vector<int> scc;
  vector<vector<int>> scc_graph;
  int scc_cnt;

  SCC(int n) :
    n(n), scc_cnt(0), dfs_cnt(0),
    adj(n + 1), scc(n + 1), dfs_order(n + 1) {
  }

  void add_edge(int a, int b) { adj[a].push_back(b); }

  void perform() {
    for (int i = 1; i <= n; i++) if (!dfs_order[i]) dfs(i);
    reconstruct();
  }
};

const int MAXN = 100;

void solve() {
  int N; cin >> N; cin.ignore();

  vector<string> reads[N]; string speaks[N];
  for (int i = 0; i < N; ++i) {
    string line; getline(cin, line);
    auto tokens = split(line, " ");
    int Z = tokens.size();

    speaks[i] = tokens[1];
    for (int j = 2; j < Z; ++j) reads[i].push_back(tokens[j]);
  }

  SCC scc(N);
  for (int i = 0; i < N; ++i) for (int j = 0; j < N; ++j) {
    if (i == j) continue;

    int ok = speaks[i] == speaks[j];
    for (string& read : reads[j]) ok |= speaks[i] == read;
    if (ok) scc.add_edge(i + 1, j + 1);
  }
  scc.perform();

  map<int, int> scc_cnt; int ans = 0;
  for (int i = 1; i <= N; ++i) {
    ans = max(ans, ++scc_cnt[scc.scc[i]]);
  }
  cout << N - ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
