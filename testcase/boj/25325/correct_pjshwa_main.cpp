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
  int N;
  cin >> N;
  vector<string> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  map<string, int> rank;
  cin.ignore();
  for (int i = 0; i < N; i++) {
    string line;
    getline(cin, line);
    for (auto token : split(line, " ")) rank[token]++;
  }

  vector<pair<int, string>> ans;
  for (int i = 0; i < N; i++) ans.push_back({rank[A[i]], A[i]});
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
