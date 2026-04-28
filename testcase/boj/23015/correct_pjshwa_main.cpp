#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int cnts[26];

void init() {
  memset(cnts, 0, sizeof(cnts));
}

void solve(int tc) {
  init();

  string s;
  cin >> s;
  bool able = true;
  int n = s.size();

  for (int i = 0; i < n; i++) cnts[s[i] - 'a']++;

  for (int i = 0; i < 26; i++) {
    if (cnts[i] * 2 > n) able = false;
  }

  string t;

  if (able) {
    vector<pair<char, int>> v;
    for (int i = 0; i < n; i++) v.push_back({s[i], i});
    sort(v.begin(), v.end());

    t.resize(n);
    for (int i = 0; i < n; i++) t[v[i].second] = v[(i + n / 2) % n].first;
  }
  else t = "IMPOSSIBLE";
  cout << "Case #" << tc << ": " << t << '\n';
}

int main() {
  fast_io();
  
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) solve(i + 1);
}
