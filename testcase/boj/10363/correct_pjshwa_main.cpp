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

const int MAXN = 20000;
int M[MAXN + 1], G[MAXN + 1];
vector<int> adj[MAXN + 1];

int rec(int v) {
  if (G[v] != -1) return G[v];

  vector<int> Gs;
  for (int u : adj[v]) {
    Gs.push_back(rec(u));
  }
  compress(Gs);

  // calculate mex of Gs
  int mex = 0;
  for (int g : Gs) {
    if (g == mex) ++mex;
    else break;
  }
  return G[v] = mex;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N; cin >> N;
  for (int i = 1; i <= N; ++i) cin >> M[i];
  for (int i = 1; i <= N; ++i) {
    G[i] = -1;
    adj[i].clear();
  }
  for (int i = 1; i <= N; ++i) {
    int x; cin >> x;
    if (x) adj[x].push_back(i);
  }

  // Each marble can be seen as a pile of stones
  // Each node can be seen as a state of the game
  int ans = 0;
  for (int i = 1; i <= N; ++i) {
    if (M[i] & 1) ans ^= rec(i);
  }
  cout << (ans ? "first\n" : "second\n");
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
