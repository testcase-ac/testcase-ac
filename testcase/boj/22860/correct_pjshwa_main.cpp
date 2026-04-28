#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 2000;
map<string, int> fi;
int fcount;
set<string> files[MAXN];
vector<int> adj[MAXN];

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

void solve() {
  int N, M; cin >> N >> M;
  for (int i = 0; i < N + M; ++i) {
    string P, F; int C; cin >> P >> F >> C;
    if (C == 0) files[fidx(P)].insert(F);
    else adj[fidx(P)].push_back(fidx(F));
  }

  map<string, int> tal;
  function<void(int)> dfs = [&](int u) {
    for (auto& f : files[u]) ++tal[f];
    for (auto& v : adj[u]) dfs(v);
  };

  int Q; cin >> Q;
  while (Q--) {
    tal.clear();

    string path_s; cin >> path_s;
    int fol_si = fidx(split(path_s, "/").back());
    dfs(fol_si);

    int kind = 0, tot = 0;
    for (auto& [f, c] : tal) ++kind, tot += c;
    cout << kind << ' ' << tot << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
