#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int N, N1, N2;
int A[24];
ll cur[3];
ll ans;
map<ll, ll> c;

void dfs1(int i) {
  if (i == N1) {
    ll diff = cur[0] - cur[1];
    if (c.count(diff)) c[diff] = min(c[diff], cur[2]);
    else c[diff] = cur[2];
    return;
  }

  for (int j = 0; j < 3; j++) {
    cur[j] += A[i];
    dfs1(i + 1);
    cur[j] -= A[i];
  }
}

void dfs2(int i) {
  if (i == N2) {
    ll diff = cur[1] - cur[0];
    if (c.count(diff)) ans = min(ans, cur[2] + c[diff]);
    return;
  }

  for (int j = 0; j < 3; j++) {
    cur[j] += A[N - i - 1];
    dfs2(i + 1);
    cur[j] -= A[N - i - 1];
  }
}

void solve() {
  ans = 0;
  for (int i = 0; i < N; i++) cin >> A[i], ans += A[i];
  N1 = N / 2, N2 = N - N1;

  c.clear();
  dfs1(0);
  dfs2(0);
  cout << ans << '\n';
}

int main() {
  fast_io();

  while (1) {
    cin >> N;
    if (N == 0) break;
    solve();
  }
}
