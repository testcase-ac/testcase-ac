#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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

const int MAXN = 1e6;
vector<int> adj[MAXN];
unordered_map<string, int> to[MAXN];
int U[MAXN], D[MAXN];

void solve() {
  int N; cin >> N;

  int it = 0;
  for (int i = 0; i < N; ++i) {
    string S; cin >> S;

    auto tokens = split(S.substr(1), "/");
    int cur = 0, Z = tokens.size();
    for (int j = 0; j < Z - 1; ++j) {
      string token = tokens[j];
      if (to[cur].count(token)) cur = to[cur][token];
      else {
        ++it;
        adj[cur].push_back(it);
        to[cur][token] = it;
        cur = it;
      }
    }
    ++U[cur]; ++D[cur];
  }

  function<void(int, int*)> dfs_l = [&](int cur, int* D) {
    for (int nxt : adj[cur]) {
      dfs_l(nxt, D);
      D[cur] += D[nxt];
    }
  };
  dfs_l(0, D);
  dfs_l(0, U); dfs_l(0, U);

  ll ans = U[0];
  function<void(int, ll)> dfs_a = [&](int cur, ll v) {
    ans = min(ans, v);
    for (int nxt : adj[cur]) {
      ll nv = v - D[nxt] + (D[0] - D[nxt]);
      dfs_a(nxt, nv);
    }
  };
  dfs_a(0, U[0]);

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
