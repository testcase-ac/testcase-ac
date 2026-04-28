#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const string common_words[] = {
  "the", "of", "for", "and", "to", "in",
  "is", "on", "that", "by", "this", "with", "you",
};

void solve() {
  string S; cin >> S;

  int common_cnt = 0;
  while (getline(cin, S)) {
    if (S.empty()) break;
    for (char& c : S) {
      if (ispunct(c)) c = ' ';
    }

    stringstream ss(S); string word;
    while (ss >> word) {
      transform(word.begin(), word.end(), word.begin(), ::tolower);
      bool ok = false;
      for (const auto& cw : common_words) {
        if (word == cw) ok = true;
      }
      common_cnt += ok;
    }
  }

  if (common_cnt >= 50) cout << "Real life\n";
  else cout << "Dreaming\n";
}

int main() {
  fast_io();
  solve();
}
