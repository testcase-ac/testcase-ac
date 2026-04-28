#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const ll MAXN = 200, INF = 1e18;

unordered_map<string, int> fi;
int fcount;
vector<int> adj[MAXN];
ll dp[MAXN][2];

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

int N;
void init() {
  fi.clear(); fcount = 0;
  for (int i = 0; i < N; ++i) {
    adj[i].clear();
    dp[i][0] = dp[i][1] = -1;
  }
}

ll dfs1(int v, int c) {
  if (dp[v][c] != -1) return dp[v][c];

  ll ret = 0;

  // Choose this vertex
  if (c == 0) {
    ll ret1 = 1;
    for (int u : adj[v]) ret1 += dfs1(u, 1);
    ret = ret1;
  }

  // Don't choose this vertex
  ll ret2 = 0;
  for (int u : adj[v]) ret2 += dfs1(u, 0);
  ret = max(ret, ret2);

  return dp[v][c] = ret;
}

int f;
void dfs2(int v, int c) {
  if (f == 1) return;
  ll ans = dfs1(v, c);

  // Choose this vertex
  ll ret1 = -INF;
  if (c == 0) {
    ret1 = 1;
    for (int u : adj[v]) ret1 += dfs1(u, 1);
  }

  // Don't choose this vertex
  ll ret2 = 0;
  for (int u : adj[v]) ret2 += dfs1(u, 0);

  if (ret1 == ans && ret1 == ret2) {
    f = 1;
    return;
  }
  if (ret1 == ans) for (int u : adj[v]) dfs2(u, 1);
  if (ret2 == ans) for (int u : adj[v]) dfs2(u, 0);
}

void solve() {
  init();

  string root; cin >> root;
  fidx(root);
  for (int i = 1; i < N; ++i) {
    string o, p; cin >> o >> p;
    int oi = fidx(o), pi = fidx(p);
    adj[pi].push_back(oi);
  }

  cout << dfs1(0, 0) << ' ';
  f = 0; dfs2(0, 0);
  if (f == 1) cout << "No\n";
  else cout << "Yes\n";
}

int main() {
  fast_io();

  while (cin >> N) {
    if (N == 0) break;
    solve();
  }
}
