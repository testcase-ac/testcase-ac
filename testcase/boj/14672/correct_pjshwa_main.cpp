#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e4;
vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], A[MAXN];
bool vis[MAXN];
vector<int> primes;

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
  int N, M; cin >> N >> M;
  for (int i = 0; i < M; ++i) {
    cin >> A[i];

    int x = A[i];
    for (int p = 2; p * p <= A[i]; ++p) {
      if (x % p) continue;
      primes.push_back(p);
      while (x % p == 0) x /= p;
    }
    if (x > 1) primes.push_back(x);
  }

  sort(primes.begin(), primes.end());
  primes.erase(unique(primes.begin(), primes.end()), primes.end());

  int Z = primes.size();
  for (int i = 0; i < M; ++i) for (int j = 0; j < Z; ++j) {
    int p = primes[j];
    if (A[i] % p == 0) adj[i].push_back(j);
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < M; i++) {
    if (ma[i] != -1) continue;
    fill(vis, vis + M, false);
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
