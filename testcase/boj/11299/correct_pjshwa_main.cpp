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

const int MAX = 50;
int points[MAX + 1];
int P, tc;

void solve() {
  cout << "Contest " << ++tc << '\n';
  for (int i = 1; i <= P; i++) cin >> points[i];

  int T;
  cin >> T;
  vector<pair<int, string>> teams(T);

  cin.ignore();
  for (int i = 0; i < T; i++) {
    string line;
    getline(cin, line);

    auto tokens = split(line, ",");
    string tname = tokens[0];
    int tscore = 0;
    for (int i = 1; i <= P; i++) {
      if (tokens[i][tokens[i].size() - 1] == '-') continue;
      tscore += points[i];
    }

    teams[i] = make_pair(tscore, tname);
  }
  sort(teams.begin(), teams.end(), [](const pair<int, string>& a, const pair<int, string>& b) {
    if (a.first == b.first) {
      string la = a.second, lb = b.second;
      transform(la.begin(), la.end(), la.begin(), ::tolower);
      transform(lb.begin(), lb.end(), lb.begin(), ::tolower);
      return la < lb;
    }
    return a.first > b.first;
  });

  int lscore = 1e9, lrank = 0;
  for (int i = 0; i < T; i++) {
    auto [tscore, tname] = teams[i];
    if (tscore != lscore) {
      lscore = tscore;
      lrank = i + 1;
    }
    cout << lrank << ' ' << tname << ' ' << tscore << '\n';
  }
}

int main() {
  fast_io();

  while (cin >> P) {
    if (P == 0) break;
    solve();
  }
}
