#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 500, INF = 1e9 + 7;

unordered_map<string, int> fi;
string inv[MAX];
int fcount;

int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    inv[fcount] = f;
    return fcount++;
  }
  else return found->second;
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

vector<int> graph[MAX];
bool vis[MAX], is_cycle[MAX];
int from[MAX];

int bfs(int v) {
  queue<pii> q;
  q.push({v, 0});
  vis[v] = true;

  while (!q.empty()) {
    auto [u, d] = q.front();
    q.pop();

    for (auto &e : graph[u]) {
      if (e == v) return from[e] = u, d + 1;

      if (vis[e]) continue;
      vis[e] = true;
      from[e] = u;
      q.push({e, d + 1});
    }
  }
  return INF;
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    fidx(s);
  }
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;

    int q;
    cin >> q;
    cin.ignore();

    while (q--) {
      string t;
      getline(cin, t);
      auto deps = split(t.substr(7), ", ");
      for (auto e : deps) graph[fidx(s)].push_back(fidx(e));
    }
  }

  int mlen = INF, mi = -1;
  for (int i = 0; i < n; i++) {
    memset(vis, 0, sizeof(vis));
    int len = bfs(i);
    if (mlen > len) {
      mlen = len;
      mi = i;
    }
  }

  if (mi == -1) cout << "SHIP IT\n";
  else {
    memset(vis, 0, sizeof(vis));
    bfs(mi);

    stack<int> traj;
    for (int i = 0; i < mlen; i++) {
      mi = from[mi];
      traj.push(mi);
    }

    while (!traj.empty()) {
      cout << inv[traj.top()] << ' ';
      traj.pop();
    }
    cout << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
