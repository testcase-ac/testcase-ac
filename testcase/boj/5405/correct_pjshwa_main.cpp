#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

pll f(ll n, ll x) {
  if (n == 0) return {0, 0};

  ll pw = 1LL << (2 * n - 2);
  ll ph = 1LL << (n - 1), r = x / pw;

  if (n % 2 == 0) {
    if (r == 0) {
      auto [px, py] = f(n - 1, x % pw);
      return {px, py};
    }
    if (r == 1) {
      auto [px, py] = f(n - 1, x % pw);
      return {py + ph, px};
    }
    if (r == 2) {
      auto [px, py] = f(n - 1, x % pw);
      return {py + ph, px + ph};
    }
    if (r == 3) {
      auto [px, py] = f(n - 1, x % pw);
      return {ph - px - 1, 2 * ph - py - 1};
    }
  }
  else {
    if (r == 0) {
      auto [px, py] = f(n - 1, x % pw);
      return {px, py};
    }
    if (r == 1) {
      auto [px, py] = f(n - 1, x % pw);
      return {py, px + ph};
    }
    if (r == 2) {
      auto [px, py] = f(n - 1, x % pw);
      return {py + ph, px + ph};
    }
    if (r == 3) {
      auto [px, py] = f(n - 1, x % pw);
      return {2 * ph - px - 1, ph - py - 1};
    }
  }
}

void solve() {
  ll n, h, o; cin >> n >> h >> o; --h; --o;

  // for (int h = 0; h < 32; ++h) {
  //   cout << "h: " << h << " ";
  //   auto [hx, hy] = f(3, h);
  //   cout << hx << " " << hy << '\n';
  // }

  auto [hx, hy] = f(n, h);
  auto [ox, oy] = f(n, o);

  ll ans = (hx - ox) * (hx - ox) + (hy - oy) * (hy - oy);
  ll ans_q = round(sqrt(ans * 100));
  cout << ans_q << "\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
