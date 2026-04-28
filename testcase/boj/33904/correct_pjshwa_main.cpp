#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

string trim(const string& s) {
  size_t start = s.find_first_not_of(" \t");
  size_t end = s.find_last_not_of(" \t");
  return (start == string::npos || end == string::npos) ? "" : s.substr(start, end - start + 1);
}

int c2i(char c) {
  if (isupper(c)) return c - 'A';
  else return c - 'a' + 26;
}

void solve() {
  vector<string> lines; string line;
  while (getline(cin, line)) lines.push_back(line);
  reverse(lines.begin(), lines.end());
  int N = lines.size();

  vector<int> seen(52, 0), decl(52, 0);
  for (char& c : lines[0]) {
    if (isalpha(c)) seen[c2i(c)] = 1;
  }

  vector<string> decls;
  for (int i = 1; i < N; ++i) {
    stringstream ss(lines[i]); string word;
    ss >> word >> word >> word;
    assert(word.size() == 1 && isalpha(word[0]));
    int idx = c2i(word[0]);
    if (!seen[idx]) continue;
    if (!decl[idx]) {
      decl[idx] = 1;
      decls.push_back(trim(lines[i]));
    }
  }
  reverse(decls.begin(), decls.end());
  decls.push_back(trim(lines[0]));

  int spc = 0;
  for (const string& decl : decls) {
    for (int i = 0; i < spc; ++i) cout << ' ';
    cout << decl << '\n';
    ++spc;
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
