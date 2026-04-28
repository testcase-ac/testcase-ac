#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
#define compress(v) sort(all(v)), v.erase(unique(all(v)), v.end())
typedef long long ll;
using namespace std;

int main() {
  int n, s, e;
  ll d;
  cin >> n;

  vector<int> xs;
  vector<pair<int, int>> yxs;

  for (int i = 0; i < n; i++) {
    cin >> s >> e;
    if (s > e) swap(s, e);
    xs.push_back(s);
    yxs.push_back({e, s});
  }
  cin >> d;
  compress(xs);
  sort(yxs.begin(), yxs.end());

  int mx = 0, yi = 0;
  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> sv;
  for (int x : xs) {
    ll ylim = d + x;
    while (yi < n && yxs[yi].first <= ylim) {
      tie(e, s) = yxs[yi++];
      sv.push({s, e});
    }
    while (!sv.empty() && sv.top().first < x) sv.pop();
    mx = max(mx, (int)sv.size());
  }

  cout << mx;
}
