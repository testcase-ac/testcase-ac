#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 100;
int parent[MAXN];
vector<int> by_group[MAXN];

int Find(int x) {
  if (x == parent[x]) return x;
  return parent[x] = Find(parent[x]);
}

void Union(int x, int y) {
  x = Find(x), y = Find(y);
  if (x != y) parent[y] = x;
}

void solve() {
  int W, N; cin >> W >> N;

  vector<tuple<int, int, int, int, int, int>> lines;
  for (int i = 0; i < N; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    int n = x2 * y1 - x1 * y2, d = x2 - x1;
    lines.emplace_back(x1, y1, x2, y2, n, d);
  }

  iota(parent, parent + N, 0);
  for (int i = 0; i < N; ++i) {
    auto [x1i, y1i, x2i, y2i, ni, di] = lines[i];
    for (int j = i + 1; j < N; ++j) {
      auto [x1j, y1j, x2j, y2j, nj, dj] = lines[j];

      // check if parallel
      if ((x2i - x1i) * (y2j - y1j) == (x2j - x1j) * (y2i - y1i)) {
        Union(i, j);
      }
    }
  }

  for (int i = 0; i < N; ++i) {
    by_group[Find(i)].push_back(i);
  }

  int tot = N, flag = 0;
  iota(parent, parent + N, 0);
  for (int g = 0; g < N; ++g) {
    flag |= (by_group[g].size() == N);

    for (int i : by_group[g]) for (int j : by_group[g]) {
      if (Find(i) == Find(j)) continue;

      auto [x1i, y1i, x2i, y2i, ni, di] = lines[i];
      auto [x1j, y1j, x2j, y2j, nj, dj] = lines[j];
      if (di == 0) {
        if (dj == 0 && x1i == x1j) {
          Union(i, j);
          --tot;
        }
      }
      else if (ni * dj == nj * di) {
        Union(i, j);
        --tot;
      }
    }
  }

  int R, ans = 0;
  if (flag) {
    R = tot + 1;
    if (R >= W) return cout << "0\n", void();
    ++ans;
    R *= 2;
  }
  else R = 2 * tot;

  if (R >= W) return cout << ans << '\n', void();
  ans += (W - R - 1) / 2 + 1;
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
