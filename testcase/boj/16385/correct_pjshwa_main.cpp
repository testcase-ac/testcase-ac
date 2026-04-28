#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int INF = 0x3f3f3f3f;
int d[20][1 << 15];

map<string, int> fi;
int fcount;
int fidx(string f) {
  auto found = fi.find(f);
  if (fi.end() == found) {
    fi.insert({f, fcount});
    return fcount++;
  }
  else return found->second;
}

int dist(int ax, int ay, int bx, int by) {
  return abs(ax - bx) + abs(ay - by);
}

void solve() {
  int n;
  cin >> n;

  vector<tuple<int, int, int>> data;
  for (int i = 0; i < n; i++) {
    int x, y; string s;
    cin >> x >> y >> s;
    data.push_back({x, y, fidx(s)});
  }

  for (int i = 0; i < 20; i++) for (int j = 0; j < (1 << 15); j++) d[i][j] = INF;
  for (int i = 0; i < n; i++) {
    auto [cx, cy, cj] = data[i];
    d[i][(1 << cj)] = dist(0, 0, cx, cy);
  }

  for (int u = 1; u < (1 << fcount); u++) {
    for (int i = 0; i < n; i++) {
      auto [cx, cy, cj] = data[i];
      if (!(u & (1 << cj))) continue;

      for (int l = 0; l < n; l++) {
        auto [lx, ly, lj] = data[l];
        if (!(u & (1 << lj))) continue;
        if (i == l) continue;

        d[i][u] = min(d[i][u], d[l][u ^ (1 << cj)] + dist(cx, cy, lx, ly));
      }
    }
  }

  int ans = INF;
  for (int i = 0; i < n; i++) {
    auto [cx, cy, cj] = data[i];
    ans = min(ans, d[i][(1 << fcount) - 1] + dist(0, 0, cx, cy));
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
