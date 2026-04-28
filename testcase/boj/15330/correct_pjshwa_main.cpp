#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 16;
int X[MAXN], Y[MAXN], N, ans;
bool vis[MAXN];
vector<pii> pairs;

void cal() {
  map<pii, int> by_slope;
  for (auto [i, j] : pairs) {
    int nom = Y[j] - Y[i], den = X[j] - X[i];
    if (den == 0) ++by_slope[{1, 0}];
    else {
      int g = __gcd(nom, den);
      nom /= g, den /= g;
      if (den < 0) nom = -nom, den = -den;
      ++by_slope[{nom, den}];
    }
  }

  int cur = 0;
  for (auto [_, cnt] : by_slope) cur += cnt * (cnt - 1) / 2;
  ans = max(ans, cur);
}

void dfs(int i) {
  if (i == N) return cal();

  int si = 0;
  while (vis[si]) ++si;

  for (int sj = si + 1; sj < N; ++sj) {
    if (vis[sj]) continue;
    vis[si] = vis[sj] = true;
    pairs.push_back({si, sj});
    dfs(i + 2);
    pairs.pop_back();
    vis[si] = vis[sj] = false;
  }
}

void solve() {
  cin >> N;
  for (int i = 0; i < N; ++i) cin >> X[i] >> Y[i];

  dfs(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
