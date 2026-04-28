#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5;
int xs[MAX], ys[MAX], N;

ll fx(ll x) {
  ll ret = 0;
  for (int i = 0; i < N; i++) ret += abs(xs[i] - x - i);
  return ret;
}

ll fy(ll y) {
  ll ret = 0;
  for (int i = 0; i < N; i++) ret += abs(ys[i] - y);
  return ret;
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  cin >> N;
  for (int i = 0; i < N; i++) {
    cin >> xs[i] >> ys[i];
  }
  sort(xs, xs + N); sort(ys, ys + N);
  ll left, right;

  // Ternary search
  left = xs[0] - N, right = xs[N - 1] + 1;
  while (left + 3 <= right) {
    ll mid1 = left + (right - left) / 3;
    ll mid2 = right - (right - left) / 3;

    if (fx(mid1) < fx(mid2)) right = mid2;
    else left = mid1;
  }
  ll addx = 1e18;
  for (ll i = left; i <= right; i++) addx = min(addx, fx(i));

  // Ternary search
  left = ys[0], right = ys[N - 1] + 1;
  while (left + 3 <= right) {
    ll mid1 = left + (right - left) / 3;
    ll mid2 = right - (right - left) / 3;

    if (fy(mid1) < fy(mid2)) right = mid2;
    else left = mid1;
  }
  ll addy = 1e18;
  for (ll i = left; i <= right; i++) addy = min(addy, fy(i));

  cout << addx + addy << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
