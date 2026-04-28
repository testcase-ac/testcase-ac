#include <bits/stdc++.h>
#define ll long long
using namespace std;

int parent[51];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void Union(int x, int y) {
  x = Find(x);
  y = Find(y);

  if (x != y) parent[y] = x;
}

int main() {
  int v;
  cin >> v;

  vector<tuple<int, int, int>> ta;
  ll tsum = 0;
  for (int i = 1; i <= v; i++) {
    string s;
    cin >> s;
    for (int j = 1; j <= v; j++) {
      char c = s[j - 1];
      if (c == '0') continue;
      int dist = 'a' <= c && c <= 'z' ? c - 'a' + 1 : c - 'A' + 27;
      ta.push_back({dist, i, j});
      tsum += dist;
    }
  }
  for (int i = 1; i <= v; i++) parent[i] = i;
  sort(ta.begin(), ta.end());

  ll ans = 0;
  int uc = 0;
  for (auto [w, x, y] : ta) {
    if (Find(x) == Find(y)) continue;
    uc++;
    ans += w;
    Union(x, y);
  }

  if (uc == v - 1) cout << tsum - ans << '\n';
  else cout << "-1\n";
}
