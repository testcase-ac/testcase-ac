#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int coins[100];
bool vis[10001];
int main() {
  fast_io();

  int n, k;
  cin >> n >> k;
  for (int i = 0; i < n; i++) cin >> coins[i];
  queue<pii> q;
  q.push({k, 0}); // Amount, steps

  int rem, stp, ans = -1;
  while (!q.empty()) {
    tie(rem, stp) = q.front();
    q.pop();

    if (vis[rem]) continue;
    vis[rem] = true;

    if (rem == 0) {
      ans = stp;
      break;
    }

    for (int i = 0; i < n; i++) {
      if (rem >= coins[i] && !vis[rem - coins[i]]) q.push({rem - coins[i], stp + 1});
    }
  }

  cout << ans << '\n';
}
