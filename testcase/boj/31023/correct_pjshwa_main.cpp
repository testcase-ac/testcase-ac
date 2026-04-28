#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N; cin >> N;

  set<string> words;
  for (int i = 0; i < N; ++i) {
    string word; cin >> word;
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return tolower(c); });
    words.insert(word);
  }

  int L; cin >> L; cin.ignore();
  int tot = 0, cnt = 0;
  for (int i = 0; i < L; ++i) {
    string line, word = ""; getline(cin, line);
    for (char c : line) {
      if (isalpha(c)) word += tolower(c);
      else if (!word.empty()) {
        ++tot;
        if (words.find(word) != words.end()) ++cnt;
        word = "";
      }
    }
    if (!word.empty()) {
      ++tot;
      if (words.find(word) != words.end()) ++cnt;
    }
  }

  if (cnt * 4 >= tot * 3) cout << "It's a hit!\n";
  else cout << "Delete immediately!\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
