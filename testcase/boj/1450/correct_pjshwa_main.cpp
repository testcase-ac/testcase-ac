#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int s[2];
ll w[2][15];
vector<ll> g[2];
vector<ll> current;

void dfs(int i, int group) {
  if (i == s[group]) {
    ll cv = 0;
    for (ll c : current) cv += c;
    g[group].push_back(cv);
    return;
  }

  dfs(i + 1, group);
  current.push_back(w[group][i]);
  dfs(i + 1, group);
  current.pop_back();
}

int main() {
  fast_io();

  ll n, c;
  cin >> n >> c;
  s[0] = n / 2;
  s[1] = n - s[0];
  for (int i = 0; i < s[0]; i++) cin >> w[0][i];
  for (int i = 0; i < s[1]; i++) cin >> w[1][i];

  dfs(0, 0);
  dfs(0, 1);

  sort(g[1].begin(), g[1].end());
  ll cnt = 0;
  for (ll v : g[0]) {
    cnt += upper_bound(g[1].begin(), g[1].end(), c - v) - g[1].begin();
  }
  cout << cnt << '\n';
}
