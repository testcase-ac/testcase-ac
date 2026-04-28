#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  int x, y;
  cin >> x >> y;
  if (x < y) swap(x, y);
  if (x <= 1 || y <= 1) {
    cout << x + y << '\n';
    return;
  }

  int xlb = x - 1, xub = x + 1, ylb = y - 1, yub = y + 1;
  while (xlb >= 2 && !is_prime(xlb)) xlb--;
  while (!is_prime(xub)) xub++;
  while (ylb >= 2) {
    if (is_prime(ylb) && (xlb - 1) / ylb == xub / ylb) break;
    else ylb--;
  }
  while (1) {
    if (is_prime(yub) && (xlb - 1) / yub == xub / yub) break;
    else yub++;
  }

  queue<pii> q;
  map<pii, ll> cdist;
  cdist[{x, y}] = 0;
  q.push({x, y});

  ll ans = -1;
  while (!q.empty()) {
    auto [x, y] = q.front(); q.pop();

    if (x <= 1 || y <= 1) {
      if (ans == -1) ans = cdist[{x, y}] + x + y;
      else ans = min(ans, cdist[{x, y}] + x + y);
      continue;
    }
    if (is_prime(x) && is_prime(y)) {
      if (ans == -1) ans = cdist[{x, y}] + x + y;
      else ans = min(ans, cdist[{x, y}] + x + y);
      continue;
    }

    for (int k = 0; k < 4; k++) {
      int nx = x + dx[k], ny = y + dy[k];
      if (nx < xlb || nx > xub || ny < ylb || ny > yub) continue;
      if (nx > 1 && ny > 1 && __gcd(nx, ny) > 1) continue;

      if (!cdist.count({nx, ny})) {
        cdist[{nx, ny}] = cdist[{x, y}] + 1;
        q.push({nx, ny});
      }
    }
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
