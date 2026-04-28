#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
#define plpll pair<ll, pll>
using namespace std;

pll ratios[10][10];
pll relative_ratios[10];
vector<plpll> graph[10];
bool vis[10];
ll lcm (ll x, ll y){ return x / __gcd(x, y) * y; }

int main() {
  ll n, a, b, p, q;
  cin >> n;

  if (n == 1) {
    cout << "1\n";
    return 0;
  }

  for (int i = 0; i < n - 1; i++) {
    cin >> a >> b >> p >> q;
    graph[a].push_back({b, {p, q}});
    graph[b].push_back({a, {q, p}});
  }

  queue<plpll> rq;
  ll idx, nidx;
  pll ratio, nratio;
  rq.push({0, {1, 1}});

  while (!rq.empty()) {
    tie(idx, ratio) = rq.front();
    rq.pop();

    if (vis[idx]) continue;
    vis[idx] = true;
    relative_ratios[idx] = ratio;

    for (auto &e : graph[idx]) {
      tie(nidx, nratio) = e;
      if (vis[nidx]) continue;
      rq.push({nidx, {ratio.first * nratio.second, ratio.second * nratio.first}});
    }
  }

  ll l = relative_ratios[0].second;
  for (int i = 1; i < n; i++) l = lcm(l, relative_ratios[i].second);
  for (int i = 0; i < n; i++) relative_ratios[i].first *= (l / relative_ratios[i].second);

  ll g = relative_ratios[0].first;
  for (int i = 1; i < n; i++) g = __gcd(g, relative_ratios[i].first);
  for (int i = 0; i < n; i++) cout << relative_ratios[i].first / g << ' ';
  cout << '\n';
}
