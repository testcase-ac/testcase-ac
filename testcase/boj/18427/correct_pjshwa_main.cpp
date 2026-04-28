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

const int MAX = 100, MOD = 10'007;
int d[MAX][1001];

void solve() {
  int n, h;
  cin >> n >> h >> h;

  cin.ignore();
  for (int i = 0; i < n; i++) {
    string s;
    getline(cin, s);
    auto args = split(s, " ");

    if (i == 0) {
      d[0][0] = 1;
      for (auto& arg : args) d[0][stoi(arg)] = 1;
    }
    else {
      for (int hi = 0; hi <= 1000; hi++) {
        d[i][hi] = d[i - 1][hi];
        for (auto& arg : args) {
          int hj = stoi(arg);
          if (hi >= hj) d[i][hi] = (d[i][hi] + d[i - 1][hi - hj]) % MOD;
        }
      }
    }
  }

  cout << d[n - 1][h] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
