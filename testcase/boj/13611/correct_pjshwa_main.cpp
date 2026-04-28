#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int p[MAX + 1];
bool vis[MAX + 1];
int cc;

void dfs(int v) {
  vis[v] = 1;
  cc++;
  if (!vis[p[v]]) dfs(p[v]);
}

ll lcm(ll a, ll b) {
  return a / __gcd(a, b) * b;
}

void solve() {
  int N;
  cin >> N;
  N /= 2;

  for (int i = 1; i <= N; i++) p[i] = 2 * i;
  for (int i = N + 1; i <= 2 * N; i++) p[i] = 2 * (i - N) - 1;

  ll g = 1;
  for (int i = 1; i <= 2 * N; i++) {
    if (vis[i]) continue;

    cc = 0;
    dfs(i);
    g = lcm(g, cc);
  }
  cout << g << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
