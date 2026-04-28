#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

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

const int MAXN = 22, MAXV = 10;
int d[MAXN + 1][MAXV + 1][MAXV + 1][MAXV + 1], N;
string P[MAXN + 1];

int r(int i, int a, int b, int c) {
  if (d[i][a][b][c] != -1) return d[i][a][b][c];
  if (a == 0 && b == 0 && c == 0) return d[i][a][b][c] = 1;
  if (i == N) return d[i][a][b][c] = 0;

  bool ret = false;
  for (char o : P[i]) {
    if (o == 'O') {
      if (a > 0) ret |= r(i + 1, a - 1, b, c);
    }
    if (o == 'V') {
      if (b > 0) ret |= r(i + 1, a, b - 1, c);
    }
    if (o == 'N') {
      if (c > 0) ret |= r(i + 1, a, b, c - 1);
    }
  }
  return d[i][a][b][c] = ret;
}

void solve() {
  int Q; cin >> Q;
  vector<tii> queries;
  for (int i = 0; i < Q; i++) {
    string S; cin >> S;
    auto tokens = split(S, "-");
    queries.push_back({stoi(tokens[0]), stoi(tokens[1]), stoi(tokens[2])});
  }

  cin >> N;
  for (int i = 0; i < N; i++) cin >> P[i];

  memset(d, -1, sizeof(d));
  for (auto& [x, y, z] : queries) {
    if (r(0, x, y, z)) cout << "DA\n";
    else cout << "NE\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
