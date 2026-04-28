#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 4e5 + 10;
vector<int> graph[MAX];
int indegree[MAX];

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

int main() {
  fast_io();

  int n;
  cin >> n;
  set<string> names;
  for (int i = 0; i < n; i++) {
    string s, t;
    cin >> s >> t;

    names.insert(s); names.insert(t);
    graph[fidx(s)].push_back(fidx(t));
    indegree[fidx(t)]++;
  }

  vector<pair<string, int>> cround, nround;
  for (int i = 0; i < fcount; i++) {
    if (!indegree[i]) cround.push_back({inv[i], i});
  }

  // One round of purchase = one loop
  int processed = 0;
  int rounds = 0;
  vector<pair<int, string>> ans;
  while (1) {
    if (cround.empty()) {
      if (processed == fcount) break;
      else return cout << "-1\n", 0;
    }

    for (auto [name, idx] : cround) {
      ans.push_back({rounds, name});
      processed++;
      for (int dst : graph[idx]) {
        if (!--indegree[dst]) nround.push_back({inv[dst], dst});
      }
    }

    cround = nround;
    nround.clear();
    rounds++;
  }

  sort(ans.begin(), ans.end());
  for (auto [round, name] : ans) cout << name << '\n';
}
