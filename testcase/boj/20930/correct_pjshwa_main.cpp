#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5, INF = 1e9 + 7;
int parent[MAX + 1];

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

void solve() {
  int N, Q;
  cin >> N >> Q;
  for (int i = 1; i <= N; i++) parent[i] = i;

  vector<tuple<int, int, int, int, int>> S(N);
  int laste, lasti;
  for (int i = 0; i < N; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    S[i] = {x1, y1, x2, y2, i + 1};
  }

  sort(S.begin(), S.end(), [] (const auto& a, const auto& b) {
    auto [ax1, ay1, ax2, ay2, ai] = a;
    auto [bx1, by1, bx2, by2, bi] = b;

    int axs = min(ax1, ax2), axe = max(ax1, ax2);
    int bxs = min(bx1, bx2), bxe = max(bx1, bx2);

    if (axs == bxs) return axe < bxe;
    else return axs < bxs;
  });

  laste = -INF, lasti = -1;
  for (int i = 0; i < N; i++) {
    auto [ax1, ay1, ax2, ay2, ai] = S[i];
    int axs = min(ax1, ax2), axe = max(ax1, ax2);

    if (laste >= axs) Union(ai, lasti);
    if (laste <= axe) {
      laste = axe;
      lasti = ai;
    }
  }

  sort(S.begin(), S.end(), [] (const auto& a, const auto& b) {
    auto [ax1, ay1, ax2, ay2, ai] = a;
    auto [bx1, by1, bx2, by2, bi] = b;

    int ays = min(ay1, ay2), aye = max(ay1, ay2);
    int bys = min(by1, by2), bye = max(by1, by2);

    if (ays == bys) return aye < bye;
    else return ays < bys;
  });

  laste = -INF, lasti = -1;
  for (int i = 0; i < N; i++) {
    auto [ax1, ay1, ax2, ay2, ai] = S[i];
    int ays = min(ay1, ay2), aye = max(ay1, ay2);

    if (laste >= ays) Union(ai, lasti);
    if (laste <= aye) {
      laste = aye;
      lasti = ai;
    }
  }

  while (Q--) {
    int u, v;
    cin >> u >> v;
    cout << (Find(u) == Find(v)) << '\n';
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
