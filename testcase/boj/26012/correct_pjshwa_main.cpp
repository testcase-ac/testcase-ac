#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 750, MAXL = 2e7;
vector<int> pr; int lp[MAXL + 1];

vector<int> adj[MAXN];
int ma[MAXN], mb[MAXN], A[MAXN];
bool vis[MAXN];

bool is_prime(int n) {
  return n > 1 && lp[n] == n;
}

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
  sort(A, A + N, greater<int>());
  while (N > 1 && A[N - 1] == A[N - 2] && A[N - 1] == 1) --N;

  for (int i = 0; i < N; ++i) {
    if (A[i] % 2 == 0) continue;
    for (int j = 0; j < N; ++j) {
      if (A[j] % 2 == 1) continue;
      if (is_prime(A[i] + A[j])) adj[i].push_back(j);
    }
  }

  int match = 0;
  memset(ma, -1, sizeof ma);
  memset(mb, -1, sizeof mb);

  for (int i = 0; i < N; ++i) {
    if (ma[i] != -1) continue;
    if (A[i] % 2 == 0) continue;
    fill(vis, vis + N, false);
    if (dfs(i)) ++match;
  }

  cout << N - match << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXL; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXL; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
