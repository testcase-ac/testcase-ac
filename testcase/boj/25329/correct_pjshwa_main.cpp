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

int t2p(int t) {
  if (t <= 100) return 10;
  t -= 100;
  return ((t - 1) / 50 + 1) * 3 + 10;
}

void solve() {
  int N;
  cin >> N;

  map<string, int> n2t;
  for (int i = 0; i < N; i++) {
    string s, name;
    cin >> s >> name;

    auto tokens = split(s, ":");
    int t = stoi(tokens[0]) * 60 + stoi(tokens[1]);
    n2t[name] += t;
  }

  vector<pair<int, string>> ans;
  for (auto [name, t] : n2t) ans.push_back({t2p(t), name});
  sort(ans.begin(), ans.end(), [] (const auto &a, const auto &b) {
    if (a.first == b.first) return a.second < b.second;
    return a.first > b.first;
  });

  for (auto [k, v] : ans) cout << v << ' ' << k << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
