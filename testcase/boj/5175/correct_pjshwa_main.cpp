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

int tc;
void solve() {
  cout << "Data Set " << ++tc << ":";

  int M, N;
  cin >> M >> N;

  cin.ignore();
  int cov[N] = {0};
  for (int i = 0; i < N; i++) {
    string line;
    getline(cin, line);
    for (auto& token : split(line, " ")) {
      if (token == "") continue;

      int x = stoi(token); x--;
      cov[i] |= 1 << x;
    }
  }

  int mu = N, mans = (1 << N) - 1;
  for (int u = 0; u < (1 << N); u++) {
    int cu = __builtin_popcount(u), acov = 0;
    for (int i = 0; i < N; i++) {
      if (u & (1 << i)) acov |= cov[i];
    }

    if (mu > cu && acov == (1 << M) - 1) {
      mu = cu;
      mans = u;
    }
  }

  for (int i = 0; i < N; i++) {
    if (mans & (1 << i)) cout << ' ' << (char)(i + 'A');
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) {
    solve();
    if (t) cout << '\n';
  }
}
