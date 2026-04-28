#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

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

  map<int, string> category_map;
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    auto tokens = split(line, " ");

    string category = tokens[tokens.size() - 2];
    int video_id = stoi(tokens[tokens.size() - 1]);
    category_map[video_id] = category;
  }

  while (m--) {
    string date_str, time_str, op_str;
    cin >> date_str >> time_str >> op_str;

    auto date_tokens = split(date_str, "-");
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
