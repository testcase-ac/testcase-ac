#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

string s;
int cost[26], d[2000][2000];

int rec(int l, int r) {
  if (l >= r) return 0;
  if (s[l] == s[r]) return rec(l + 1, r - 1);
  int &ret = d[l][r];
  if (ret != -1) return ret;

  return ret = min(
    rec(l + 1, r) + cost[s[l] - 'a'],
    rec(l, r - 1) + cost[s[r] - 'a']
  );
}

int main() {
  fast_io();

  memset(d, -1, sizeof(d));

  int n, m;
  cin >> n >> m >> s;
  for (int i = 0; i < n; i++) {
    string c;
    int c1, c2;
    cin >> c >> c1 >> c2;
    cost[c[0] - 'a'] = min(c1, c2);
  }
  cout << rec(0, s.size() - 1) << '\n';
}
