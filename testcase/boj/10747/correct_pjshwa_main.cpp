#include <bits/stdc++.h> 
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int fail[MAX + 1];

int main() {
  fast_io();

  string s, t;
  cin >> s >> t;

  int ssz = s.size(), tsz = t.size();
  int j = 0;
  for (int i = 1; i < tsz; i++) {
    while (t[i] != t[j] && j > 0) j = fail[j - 1];
    if (t[i] == t[j]) fail[i] = ++j;
  }

  string res = "";
  vector<int> pi(ssz, 0);
  for (int i = 0, j = 0; i < ssz; i++) {
    while (j > 0 && s[i] != t[j]) j = fail[j - 1];
    res += s[i];
    if (s[i] == t[j]) {
      if (j == tsz - 1) {
        for (int k = 0; k < tsz; k++) res.pop_back();
        j = pi[res.size()];
      }
      else j++;
    }
    pi[res.size()] = j;
  }

  cout << res << '\n';
}
