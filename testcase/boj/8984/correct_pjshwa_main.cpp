#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define getidx(v, x) (lower_bound(all(v), x) - v.begin())
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll ld[MAX], rd[MAX];

int main() {
  fast_io();

  int n, l;
  cin >> n >> l;
  vector<int> xs, ys;
  vector<pii> a(n);
  for (int i = 0; i < n; ++i) {
    int x, y;
    cin >> x >> y;
    xs.push_back(x);
    ys.push_back(y);
    a[i] = {x, y};
  }
  sort(all(a));
  compress(xs);
  compress(ys);

  for (int i = 0; i < n; ++i) {
    auto [x, y] = a[i];
    int li = getidx(xs, x), ri = getidx(ys, y);
    int score = l + abs(x - y);

    ll prevl = ld[li], prevr = rd[ri];
    ld[li] = max(ld[li], prevr + score);
    rd[ri] = max(rd[ri], prevl + score);
  }

  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    ans = max({ans, ld[i], rd[i]});
  }

  cout << ans << '\n';
}
