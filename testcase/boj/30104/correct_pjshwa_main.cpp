#include <bits/stdc++.h>
using namespace std;
using ll = long long;

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

const int MAX = 1e6;
string L[MAX + 1], P[MAX + 1];
vector<int> adj[MAX + 1];

void solve() {
  ll K; cin >> K;

  cin.ignore(); string line;
  int it = 0;
  while (getline(cin, line)) {
    ++it;

    // goto
    if (line[0] == 'G') {
      int nxt = stoi(line.substr(5));
      adj[it].push_back(nxt);
    }
    else {
      adj[it].push_back(it + 1);
      if (line[0] == 'P') {
        P[it] = line.substr(6);
      }

      // assignment
      else {

      }
    }
  }

  int E = it + 1;
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
