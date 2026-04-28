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

set<string> r;
map<string, vector<string>> rules;

void dfs(string c) {
  r.insert(c);
  if (r.size() > 1000) {
    cout << "Too many.\n";
    exit(0);
  }

  for (auto& [k, vv] : rules) {
    for (int i = 0; i < c.size(); i++) {
      if (c.substr(i, k.size()) != k) continue;

      for (auto& t : vv) {
        string n = c.substr(0, i) + t + c.substr(i + k.size());
        if (r.find(n) == r.end()) dfs(n);
      }
    }
  }
}

void solve() {
  string I;
  cin >> I;

  string R;
  while (cin >> R) {
    auto T = split(R, "\"->\"");
    auto S = split(T[0], "\"")[1];
    auto E = split(T[1], "\"")[0];

    rules[S].push_back(E);
  }

  dfs(I);
  cout << r.size() << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
