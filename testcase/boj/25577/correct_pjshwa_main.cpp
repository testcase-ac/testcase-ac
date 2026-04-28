#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int A[MAX], B[MAX];
bool vis[MAX];
map<int, int> pos;
int cc;

void dfs(int v) {
  vis[v] = 1;
  cc++;

  int nxt = pos[A[v]];
  if (!vis[nxt]) dfs(nxt);
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> A[i];
    B[i] = A[i];
  }
  sort(B, B + N);
  for (int i = 0; i < N; i++) pos[B[i]] = i;

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (vis[i]) continue;

    cc = 0;
    dfs(i);
    ans += (cc - 1);
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
