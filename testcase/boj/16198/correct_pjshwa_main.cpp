#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10;
int A[MAX];
bool vis[MAX];

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> A[i];

  int p[N - 2];
  for (int i = 0; i < N - 2; i++) p[i] = i + 1;

  int ans = 0;
  do {
    memset(vis, 0, sizeof(vis));
    int cur = 0;
    for (int i = 0; i < N - 2; i++) {
      int x = p[i];
      vis[x] = true;

      int l = x - 1, r = x + 1;
      while (vis[l]) l--;
      while (vis[r]) r++;
      cur += A[l] * A[r];
    }
    ans = max(ans, cur);
  } while (next_permutation(p, p + N - 2));

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
