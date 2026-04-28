#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

bool is_upper(char c) {
  return 'A' <= c && c <= 'Z';
}

bool is_lower(char c) {
  return 'a' <= c && c <= 'z';
}

bool is_cap(string& s) {
  int Z = s.size();
  if (Z < 2) return false;

  bool ok = is_upper(s[0]);
  for (int i = 1; i < Z; ++i) ok &= is_lower(s[i]);
  return ok;
}

string L;
void solve() {
  string word = ""; int Z = L.size();
  vector<string> cap_seq;

  auto print_abbv = [&](vector<string>& sv) {
    if (sv.size() == 1) {
      cout << sv[0];
      return;
    }

    for (auto& s : sv) cout << s[0];
    cout << " (";

    int Z = sv.size();
    for (int i = 0; i < Z; i++) {
      cout << sv[i];
      if (i < Z - 1) cout << ' ';
    }
    cout << ")";
  };

  auto postprocess = [&](char c, int i) {
    if (is_cap(word)) {
      cap_seq.push_back(word);
      if (!(c == ' ' && i < Z - 1 && is_upper(L[i + 1]))) {
        print_abbv(cap_seq);
        cap_seq.clear();
        cout << c;
      }
    }
    else {
      if (cap_seq.size()) {
        print_abbv(cap_seq);
        cap_seq.clear();
        cout << ' ';
      }
      cout << word << c;
    }
    word = "";
  };

  for (int i = 0; i < Z; i++) {
    char c = L[i];
    if (isalpha(c)) word += c;
    else postprocess(c, i);
  }
  postprocess('\n', Z);
}

int main() {
  fast_io();

  while (getline(cin, L)) solve();
}
