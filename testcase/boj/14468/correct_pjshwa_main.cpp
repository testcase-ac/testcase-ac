#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<int> p[26];

bool between(int s, int e, int p) {
  return s <= p && p <= e;
}

int main() {
  fast_io();

  string s;
  cin >> s;
  int sz = s.size();
  for (int i = 0; i < sz; i++) p[s[i] - 'A'].push_back(i);

  int ans = 0;
  for (int i = 0; i < 26; i++) for (int j = i + 1; j < 26; j++) {
    if (p[i][1] > p[j][0] && p[j][1] > p[i][0]) {
      if (between(p[i][0], p[i][1], p[j][0]) && between(p[i][0], p[i][1], p[j][1])) continue;
      if (between(p[j][0], p[j][1], p[i][0]) && between(p[j][0], p[j][1], p[i][1])) continue;
      ans++;
    }
  }
  cout << ans << '\n';
}
