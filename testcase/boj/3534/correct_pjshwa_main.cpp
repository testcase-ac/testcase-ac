#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

ll area(ll x11, ll y11, ll x12, ll y12, ll x21, ll y21, ll x22, ll y22) {
  ll x2 = min(x12, x22), x1 = max(x11, x21);
  ll y2 = min(y12, y22), y1 = max(y11, y21);
  return max(0LL, x2 - x1) * max(0LL, y2 - y1);
}

void solve() {
  ll xo11, yo11, xo12, yo12, xi11, yi11, xi12, yi12;
  ll xo21, yo21, xo22, yo22, xi21, yi21, xi22, yi22;
  cin >> xo11 >> yo11 >> xo12 >> yo12 >> xi11 >> yi11 >> xi12 >> yi12;
  cin >> xo21 >> yo21 >> xo22 >> yo22 >> xi21 >> yi21 >> xi22 >> yi22;

  if (xo11 > xo12) swap(xo11, xo12);
  if (yo11 > yo12) swap(yo11, yo12);
  if (xi11 > xi12) swap(xi11, xi12);
  if (yi11 > yi12) swap(yi11, yi12);
  if (xo21 > xo22) swap(xo21, xo22);
  if (yo21 > yo22) swap(yo21, yo22);
  if (xi21 > xi22) swap(xi21, xi22);
  if (yi21 > yi22) swap(yi21, yi22);

  vector<ll> xs1 = {xo11, xo12, xi11, xi12};
  vector<ll> ys1 = {yo11, yo12, yi11, yi12};
  vector<ll> xs2 = {xo21, xo22, xi21, xi22};
  vector<ll> ys2 = {yo21, yo22, yi21, yi22};

  ll ans = 0, tx = 0, ty = 0;
  for (ll x1 : xs1) for (ll x2 : xs2) for (ll y1 : ys1) for (ll y2 : ys2) {
    ll dx = x1 - x2, dy = y1 - y2;
    ll nxo21 = xo21 + dx, nxo22 = xo22 + dx;
    ll nyo21 = yo21 + dy, nyo22 = yo22 + dy;
    ll nxi21 = xi21 + dx, nxi22 = xi22 + dx;
    ll nyi21 = yi21 + dy, nyi22 = yi22 + dy;

    ll tarea = area(xo11, yo11, xo12, yo12, nxo21, nyo21, nxo22, nyo22);
    tarea -= area(xo11, yo11, xo12, yo12, nxi21, nyi21, nxi22, nyi22);
    tarea -= area(xi11, yi11, xi12, yi12, nxo21, nyo21, nxo22, nyo22);
    tarea += area(xi11, yi11, xi12, yi12, nxi21, nyi21, nxi22, nyi22);

    if (ans < tarea) ans = tarea, tx = dx, ty = dy;
  }
  cout << ans << '\n' << tx << ' ' << ty << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
