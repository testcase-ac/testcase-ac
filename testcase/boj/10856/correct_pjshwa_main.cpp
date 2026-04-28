#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
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

const int MAXN = 400;
vector<int> adj[MAXN];
int vis[MAXN];

void solve() {
  int N; cin >> N;

  queue<int> Q;
  for (int i = 0; i < N; ++i) {
    string P; int ki; cin >> P >> ki;
    while (ki--) {
      string T; cin >> T;
      adj[fidx(T)].push_back(fidx(P));
    }

    auto tokens = split(P, ":");
    if (tokens.back() == "PROGRAM") Q.push(fidx(P)), vis[fidx(P)] = 1;
  }

  while (!Q.empty()) {
    int u = Q.front(); Q.pop();
    for (int v : adj[u]) {
      if (!vis[v]) Q.push(v), vis[v] = 1;
    }
  }

  int ans = N;
  for (int i = 0; i < N; ++i) ans -= vis[i];
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
