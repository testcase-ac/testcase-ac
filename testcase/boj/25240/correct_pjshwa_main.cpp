#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

void solve() {
  int n, m;
  cin >> n >> m;
  cin.ignore();

  map<string, vector<string>> ugroups;
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    auto tokens = split(line, " ");

    if (tokens.size() == 1) {
      auto user = tokens[0];
      ugroups[user] = {user};
    }
    else {
      auto user = tokens[0];
      ugroups[user] = split(tokens[1], ",");
      ugroups[user].push_back(user);
    }

  }

  map<string, vector<string>> files;
  for (int i = 0; i < m; i++) {
    string line;
    getline(cin, line);
    auto tokens = split(line, " ");

    files[tokens[0]] = {tokens[1], tokens[2], tokens[3]};
  }

  int q;
  cin >> q;
  cin.ignore();

  while (q--) {
    string line;
    getline(cin, line);
    auto tokens = split(line, " ");

    string user = tokens[0], file = tokens[1], op = tokens[2];
    auto finfo = files[file];

    string perm = finfo[0], fowner = finfo[1], fgroup = finfo[2];

    int pmask = perm[2] - '0';
    if (user == fowner) pmask = perm[0] - '0';
    else {
      auto groups = ugroups[user];
      for (auto group : groups) {
        if (group == fgroup) {
          pmask = perm[1] - '0';
          break;
        }
      }
    }

    if (op == "R") cout << (pmask & 4 ? 1 : 0) << '\n';
    if (op == "W") cout << (pmask & 2 ? 1 : 0) << '\n';
    if (op == "X") cout << (pmask & 1 ? 1 : 0) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
