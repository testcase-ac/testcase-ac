#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int C[MAX + 1], parent[MAX + 1];
ll ans[MAX + 1];
set<int> S[MAX + 1];
map<int, int> T[MAX + 1];

int Find(int x) {
  if (x == parent[x]) return x;
  else {
    int p = Find(parent[x]);
    parent[x] = p;
    return p;
  }
}

void solve() {
  int N, K, M; cin >> N >> K >> M;
  for (int i = 1; i <= N; i++) {
    cin >> C[i];
    parent[i] = i;
    S[i].insert(i);
    T[i][C[i]] = 1;
  }

  vector<tuple<int, int, int>> E;
  for (int i = 0; i < M; i++) {
    int x, y, w; cin >> x >> y >> w;
    E.emplace_back(w, x, y);
  }
  sort(E.begin(), E.end(), greater<>());

  for (auto [w, x, y] : E) {
    x = Find(x), y = Find(y);
    if (x == y) continue;

    if (S[x].size() < S[y].size()) swap(x, y);

    parent[y] = x;
    for (int d : S[y]) {
      S[x].insert(d); int c = C[d];
      ans[c] += (ll)w * T[x][c];
    }
    for (auto [c, cnt] : T[y]) T[x][c] += cnt;
    S[y].clear(); T[y].clear();
  }

  for (int i = 1; i <= K; i++) cout << ans[i] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
