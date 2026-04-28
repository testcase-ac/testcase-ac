#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

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

const int MAXN = 1e4;
vector<int> adj[MAXN];
int cdist[MAXN];

int P, N, tc;
void solve() {
  if (++tc > 1) cout << '\n';
  cout << "Database #" << tc << '\n';

  for (int i = 0; i < fcount; ++i) adj[i].clear();
  fcount = 0; fi.clear();

  cin.ignore();
  while (P--) {
    string line; getline(cin, line);
    auto tokens = split(line, ":");
    assert(tokens.size() == 2);

    auto names = split(tokens[0], ", ");
    assert(names.size() % 2 == 0);

    int Z = names.size();
    vector<int> names_idx;
    for (int i = 0; i < Z; i += 2) {
      auto fname = names[i] + ", " + names[i + 1];
      names_idx.push_back(fidx(fname));
    }

    for (int i1 : names_idx) for (int i2 : names_idx) {
      if (i1 == i2) continue;
      adj[i1].push_back(i2);
      adj[i2].push_back(i1);
    }
  }

  int T = fcount;
  fill(cdist, cdist + T, -1);
  queue<int> q; int x = fidx("Erdos, P.");
  cdist[x] = 0; q.push(x);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : adj[u]) {
      if (cdist[v] == -1) {
        cdist[v] = cdist[u] + 1;
        q.push(v);
      }
    }
  }

  while (N--) {
    string fname; getline(cin, fname);
    cout << fname << ": ";

    int idx = fidx(fname);
    if (idx >= T || cdist[idx] == -1) cout << "infinity\n";
    else cout << cdist[idx] << '\n';
  }
}

int main() {
  fast_io();

  while (cin >> P >> N) {
    if (P == 0 && N == 0) break;
    solve();
  }
}
