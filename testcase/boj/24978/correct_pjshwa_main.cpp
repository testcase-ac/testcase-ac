#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int fs[26], ft[26];
bool pw[26][26];

void solve() {
  string s, t; int q;
  cin >> s >> t >> q;
  for (int i = 0; i < s.size(); i++) fs[s[i] - 'a']++;
  for (int i = 0; i < t.size(); i++) ft[t[i] - 'a']++;

  for (int i = 0; i < 26; i++) for (int j = i + 1; j < 26; j++) {
    string ns = "", nt = "";
    for (char& c : s) if (c - 'a' == i || c - 'a' == j) ns += c;
    for (char& c : t) if (c - 'a' == i || c - 'a' == j) nt += c;
    pw[i][j] = pw[j][i] = ns == nt;
  }

  while (q--) {
    string qs;
    cin >> qs;

    int ssum = 0, tsum = 0;
    for (char& c : qs) {
      ssum += fs[c - 'a'];
      tsum += ft[c - 'a'];
    }

    if (ssum != tsum) {
      cout << 'N';
      continue;
    }

    int qz = qs.size();

    bool able = true;
    for (int i = 0; i < qz; i++) for (int j = i + 1; j < qz; j++) {
      if (!pw[qs[i] - 'a'][qs[j] - 'a']) able = false;
    }

    if (able) cout << 'Y';
    else cout << 'N';
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
