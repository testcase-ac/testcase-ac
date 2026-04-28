#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int lp[MAX + 1];
vector<int> pr;

bool vis[MAX + 1];

void solve() {
  int n, a, b;
  cin >> n >> a >> b;

  memset(vis, 0, sizeof(vis));

  queue<pii> q;
  q.push({n, 0});
  vis[n] = true;

  while (!q.empty()) {
    auto [v, d] = q.front();
    q.pop();

    if (a <= v && v <= b && lp[v] == v) return cout << d << '\n', void();

    if (!vis[v / 2]) {
      q.push({v / 2, d + 1});
      vis[v / 2] = true;
    }
    if (!vis[v / 3]) {
      q.push({v / 3, d + 1});
      vis[v / 3] = true;
    }
    if (v + 1 <= MAX && !vis[v + 1]) {
      q.push({v + 1, d + 1});
      vis[v + 1] = true;
    }
    if (v - 1 >= 0 && !vis[v - 1]) {
      q.push({v - 1, d + 1});
      vis[v - 1] = true;
    }
  }

  cout << "-1\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
