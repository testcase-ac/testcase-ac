#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const string words[26] = {
  "aespa",
  "baekjoon",
  "cau",
  "debug",
  "edge",
  "firefox",
  "golang",
  "haegang",
  "iu",
  "java",
  "kotlin",
  "lol",
  "mips",
  "null",
  "os",
  "python",
  "query",
  "roka",
  "solvedac",
  "tod",
  "unix",
  "virus",
  "whale",
  "xcode",
  "yahoo",
  "zebra"
};

void solve() {
  string S;
  cin >> S;
  int n = S.size();

  string ans = "";
  int i = 0;
  while (i < n) {
    char c = S[i];
    string w = words[c - 'a'];
    if (S.substr(i, w.size()) == w) {
      ans += c;
      i += w.size();
    }
    else {
      cout << "ERROR!\n";
      return;
    }
  }

  cout << "It's HG!\n";
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
