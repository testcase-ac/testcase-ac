#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
const ll INF = 1e18;
vector<int> graph[MAX + 1];
int t[MAX + 1];
bool vis[MAX + 1];

void solve() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    int ki;
    cin >> ki;
    for (int j = 0, x; j < ki; j++) {
      cin >> x;
      graph[x].push_back(i);
    }
  }

  ll ans = INF;
  for (int i = 1; i <= n; i++) {
    memset(vis, 0, sizeof vis);
    memset(t, 0, sizeof t);

    queue<pii> q;
    q.push({i, 1});
    vis[i] = 1;

    while (!q.empty()) {
      auto [u, d] = q.front();
      q.pop();

      t[d]++;
      for (int v : graph[u]) {
        if (!vis[v]) {
          vis[v] = 1;
          q.push({v, d + 1});
        }
      }
    }

    bool able = true;
    for (int j = 1; j <= n; j++) able &= vis[j];
    if (!able) continue;

    ll cur = 0;
    for (int j = 1; j <= n; j++) cur += j * t[j];
    ans = min(ans, cur);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
