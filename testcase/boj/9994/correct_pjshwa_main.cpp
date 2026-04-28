#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int dfs(string o) {
  int sz = o.size();

  int ans = 1;
  if (sz % 2 && sz > 2) {
    int half = sz / 2;

    if (o.substr(0, half) == o.substr(half, half)) ans += dfs(o.substr(half));
    if (o.substr(0, half) == o.substr(half + 1, half)) ans += dfs(o.substr(half));
    if (o.substr(0, half) == o.substr(half + 1, half)) ans += dfs(o.substr(0, half + 1));
    if (o.substr(1, half) == o.substr(half + 1, half)) ans += dfs(o.substr(0, half + 1));
  }
  return ans;
}

int main() {
  fast_io();

  string o;
  cin >> o;

  int sz = o.size();
  int ans = 0;
  if (sz & 1) {
    int half = sz / 2;

    if (o.substr(0, half) == o.substr(half, half)) ans += dfs(o.substr(half));
    if (o.substr(0, half) == o.substr(half + 1, half)) ans += dfs(o.substr(half));
    if (o.substr(0, half) == o.substr(half + 1, half)) ans += dfs(o.substr(0, half + 1));
    if (o.substr(1, half) == o.substr(half + 1, half)) ans += dfs(o.substr(0, half + 1));
  }
  cout << ans << '\n';
}
