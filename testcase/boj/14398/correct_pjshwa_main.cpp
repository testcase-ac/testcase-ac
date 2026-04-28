#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 200;
vector<int> adj[MAXN];
ll ma[MAXN], mb[MAXN], A[MAXN];
bool vis[MAXN];

bool dfs(int a) {
  vis[a] = true;
  for (int b : adj[a]) {
    if (mb[b] == -1 || (!vis[mb[b]] && dfs(mb[b]))) {
      ma[a] = b; mb[b] = a;
      return true;
    }
  }
  return false;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  for (int i = 0; i < N; ++i) {
    if (A[i] & 1) continue;
    for (int j = 0; j < N; ++j) {
      ll g = gcd(A[i], A[j]);
      if (g != 1) continue;

      ll qq = A[i] * A[i] + A[j] * A[j];
      ll q = sqrt(qq), flag = 0;
      for (ll k = max(0LL, q - 2); k <= q + 2; ++k) {
        flag |= (k * k == qq);
      }
      if (flag) adj[i].push_back(j);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    if (A[i] & 1) continue;
    memset(vis, false, sizeof vis);
    if (dfs(i)) ++match;
  }
  cout << match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
