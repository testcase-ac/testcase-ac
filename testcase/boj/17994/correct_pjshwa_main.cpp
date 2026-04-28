#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 500;
string A[MAXN];
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], K;
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

int min_swaps(string& S, string& T) {
  char C[256] = {};
  for (int i = 0; i < K; ++i) C[S[i]] = i;

  vector<int> P;
  for (int i = 0; i < K; ++i) P.push_back(C[T[i]]);

  vector<bool> vis(K, false);
  int ans = 0;
  for (int i = 0; i < K; ++i) {
    if (vis[i]) continue;
    int x = i, cnt = 0;
    while (!vis[x]) {
      vis[x] = true;
      x = P[x];
      ++cnt;
    }
    ans += cnt - 1;
  }
  return ans;
}

void solve() {
  int N; cin >> N;
  for (int i = 0; i < N; ++i) cin >> A[i];
  K = A[0].size();

  vector<int> O, E{0};
  for (int i = 1; i < N; ++i) {
    if (min_swaps(A[0], A[i]) % 2) O.push_back(i);
    else E.push_back(i);
  }

  int Oz = O.size(), Ez = E.size();
  for (int i = 0; i < Oz; ++i) for (int j = 0; j < Ez; ++j) {
    if (min_swaps(A[O[i]], A[E[j]]) == 1) adj[i].push_back(j);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < Oz; ++i) {
    if (ma[i] != -1) continue;
    fill(vis, vis + Oz, false);
    if (dfs(i)) ++match;
  }
  cout << N - match << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
