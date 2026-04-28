#include <bits/stdc++.h>
using namespace std;

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

void solve() {
  int N;
  cin >> N;

  queue<string> q[N];
  cin.ignore();
  for (int i = 0; i < N; i++) {
    string line;
    getline(cin, line);
    for (auto token : split(line, " ")) q[i].push(token);
  }

  string sentence;
  getline(cin, sentence);
  for (auto word : split(sentence, " ")) {
    bool f = false;
    for (int i = 0; i < N; i++) {
      if (q[i].empty()) continue;
      if (q[i].front() == word) {
        q[i].pop();
        f = true;
      }
    }

    if (!f) return cout << "Impossible\n", void();
  }

  for (int i = 0; i < N; i++) {
    if (!q[i].empty()) return cout << "Impossible\n", void();
  }
  cout << "Possible\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
