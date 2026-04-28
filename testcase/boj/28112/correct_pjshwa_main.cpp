#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXN = 1e6, MOD = 998244353;
int A[MAXN + 1];
vector<int> adj[MAXN + 1];

void solve() {
  int N; cin >> N;

  int root;
  for (int i = 1; i <= N; ++i) {
    int p; cin >> p;
    if (p == 0) root = i;
    else adj[p].push_back(i);
  }
  for (int i = 1; i <= N; ++i) cin >> A[i];
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
