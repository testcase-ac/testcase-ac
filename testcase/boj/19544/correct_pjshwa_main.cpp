#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll fac[501];
int a[501][501];
int cnt[501];
int n;
int chk = 0;
bool vis[501];
const int MOD = 1e9 + 7;

void dfs(int v) {
  vis[v] = true;
  chk++;
  for (int i = 1; i <= n; i++) {
    if (a[v][i] == 1 && !vis[i]) dfs(i);
  }
}

int main() {
  fast_io();

  cin >> n;

  fac[0] = 1;
  for (int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % MOD;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> a[i][j];
      cnt[i] += a[i][j];
    }
    pq.push({cnt[i], i});
  }

  ll ans = 1;
  while (!pq.empty()) {
    auto[c, v] = pq.top();
    pq.pop();
    if (vis[v]) continue;

    // Mark all cycle elements as visited
    int before = chk;
    dfs(v);
    int after = chk;
    int csize = after - before;
    ll mul = fac[csize - 1];

    int ccnt = 0;
    queue<pii> q;
    for (int i = 1; i <= n; i++) {
      if (a[i][v] == 1 && cnt[i] == c + 1) {
        ccnt++;
        q.push({i, c + 1});
      }
    }

    // Visited check for the parents
    while (!q.empty()) {
      auto[cv, cc] = q.front();
      q.pop();

      vis[cv] = true;
      bool found = false;

      for (int i = 1; i <= n; i++) {
        if (a[i][cv] == 1 && cnt[i] == cc + 1) {
          found = true;
          q.push({i, cc + 1});
        }
      }
    }

    ll tcnt = 1;
    for (int i = 0; i < ccnt; i++) tcnt = (tcnt * csize) % MOD;

    ans = (ans * mul) % MOD;
    ans = (ans * tcnt) % MOD;
  }

  cout << ans;
}
