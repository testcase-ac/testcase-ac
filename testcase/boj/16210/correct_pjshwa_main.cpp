#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
tii a[MAX];
ll xds[MAX], yds[MAX];

int main() {
  fast_io();
  
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x, y;
    cin >> x >> y;
    a[i] = make_tuple(x, y, i);
  }

  sort(a, a + n, [] (tii a, tii b) {
    return get<0>(a) < get<0>(b);
  });
  ll cur;
  cur = 0;
  for (int i = 1; i < n; i++) cur += get<0>(a[i]) - get<0>(a[0]);
  xds[get<2>(a[0])] = cur;
  for (int i = 1; i < n; i++) {
    ll diff = get<0>(a[i]) - get<0>(a[i - 1]);
    cur -= diff * (n - i);
    cur += diff * i;
    xds[get<2>(a[i])] = cur;
  }

  sort(a, a + n, [] (tii a, tii b) {
    return get<1>(a) < get<1>(b);
  });
  cur = 0;
  for (int i = 1; i < n; i++) cur += get<1>(a[i]) - get<1>(a[0]);
  yds[get<2>(a[0])] = cur;
  for (int i = 1; i < n; i++) {
    ll diff = get<1>(a[i]) - get<1>(a[i - 1]);
    cur -= diff * (n - i);
    cur += diff * i;
    yds[get<2>(a[i])] = cur;
  }

  ll ans = 1e18, mi = -1;
  for (int i = 0; i < n; i++) {
    ll x = xds[i], y = yds[i];
    if (x + y < ans) {
      ans = x + y;
      mi = i;
    }
  }
  cout << mi + 1 << '\n';
}
