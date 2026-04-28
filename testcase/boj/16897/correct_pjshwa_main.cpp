#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void compress(vector<int>& v) {
  sort(v.begin(), v.end());
  v.erase(unique(v.begin(), v.end()), v.end());
}

const int MAXN = 500;
int K, N, M, G[MAXN + 1][MAXN + 1];

int rec(int i, int j) {
  if (G[i][j] != -1) return G[i][j];

  vector<int> Gs;
  if (i < N) Gs.push_back(rec(i + 1, j));
  if (j < M) Gs.push_back(rec(i, j + 1));
  if (i + K <= N && j + K <= M) {
    Gs.push_back(rec(i + K, j + K));
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
  }
  return G[i][j] = mex;
}

void solve() {
  cin >> K >> N >> M;

  int x = min(N, M) - 1, y = max(N, M) - 1;
  if (x > y) swap(x, y);

  int ans;
  if (x % (K + 1) == K) ans = 1;
  else {
    ans = (x + y) & 1;
    int q = x / (K + 1);
    if (K > 1) ans ^= (q & 1);
  }

  // memset(G, -1, sizeof(G));

  // for (int i = 1; i <= N; ++i) {
  //   for (int j = 1; j <= M; ++j) {
  //     cout << rec(i, j) << ' ';
  //   }
  //   cout << '\n';
  // }

  if (ans) cout << "koosaga\n";
  else cout << "cubelover\n";

}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
