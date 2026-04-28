#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
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

const int MAX = 4e5;
vector<int> roots;
vector<tii> graph[MAX + 1];
bool ovis[MAX + 1], nvis[MAX + 1], refid_removed[MAX + 1];
map<int, int> obj_map, ref_map;
int ocnt = 0, oid = 0, rid = 0;

void dfs_s(int u) {
  nvis[u] = 1;
  ocnt++;
  for (auto& [v, ref_id, w] : graph[u]) {
    if (!ovis[v]) continue;
    if (!w) continue;
    if (refid_removed[ref_id]) continue;
    if (nvis[v]) continue;
    dfs_s(v);
  }
}

void dfs_w(int u) {
  nvis[u] = 1;
  ocnt++;
  for (auto& [v, ref_id, w] : graph[u]) {
    if (!ovis[v]) continue;
    if (refid_removed[ref_id]) continue;
    if (nvis[v]) continue;
    dfs_w(v);
  }
}

void solve() {
  int o, e;
  cin >> o >> e;

  for (int i = 0; i < o; i++) {
    int object_id;
    string is_root;
    cin >> object_id >> is_root;
    obj_map[object_id] = ++oid;
    ovis[oid] = 1;
    if (is_root == "ROOT") roots.push_back(oid);
  }

  cin.ignore();
  while (e--) {
    string command;
    getline(cin, command);

    if (command == "m") {
      memset(nvis, 0, sizeof(nvis));
      ocnt = 0;
      for (int u : roots) {
        if (!nvis[u]) dfs_w(u);
      }
      cout << ocnt << '\n';
      for (int i = 1; i <= oid; i++) ovis[i] = nvis[i];
    }
    else if (command == "M") {
      memset(nvis, 0, sizeof(nvis));
      ocnt = 0;
      for (int u : roots) {
        if (!nvis[u]) dfs_s(u);
      }
      cout << ocnt << '\n';
      for (int i = 1; i <= oid; i++) ovis[i] = nvis[i];
    }
    else {
      auto args = split(command, " ");
      if (args[0] == "MADE") {
        obj_map[stoi(args[1])] = ++oid;
        ovis[oid] = 1;
        if (args[2] == "ROOT") roots.push_back(oid);
      }
      if (args[0] == "ADD") {
        int u = obj_map[stoi(args[2])];
        int v = obj_map[stoi(args[4])];
        ref_map[stoi(args[1])] = ++rid;
        if (args[3] == "->") graph[u].push_back({v, rid, 0});
        else graph[u].push_back({v, rid, 1});
      }
      if (args[0] == "REMOVE") {
        int ref_id = stoi(args[1]);
        refid_removed[ref_map[ref_id]] = 1;
      }
    }
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
