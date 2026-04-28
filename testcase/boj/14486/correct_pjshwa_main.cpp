#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n;
  cin >> n;

  priority_queue<pii> pq;
  vector<pii> coords;
  vector<int> xs;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    coords.emplace_back(x, y);
    xs.emplace_back(x);
  }
  compress(xs);
  sort(coords.begin(), coords.end());

  int xi = 0, ci = 0;
  ll asum = 0, rsum = 0;
  while (ci < n) {
    while (ci < n && get<0>(coords[ci]) <= xs[xi]) {
      pq.push({get<1>(coords[ci]), get<2>(coords[ci])});
      rsum += get<2>(coords[ci]);
      ci++;
    }

    while (pq.size() > c) {
      rsum -= pq.top().second;
      pq.pop();
    }

    asum = max(asum, rsum);
    xi++;
  }

  cout << asum << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
