#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll lpow(ll x, ll y, ll m) {
  ll r = 1;
  x %= m;
  while (y) {
    if (y & 1) r = (r * x) % m;
    x = (x * x) % m;
    y >>= 1;
  }
  return r;
}

vector<pii> ans;

void dissect(int opow2, ll n) {
  int pow2 = 1, pow3 = 1;

  while (lpow(3, pow3, 1e18) <= n) pow3++;
  ans.push_back({opow2, pow3 - 1});
  ll rem = n - lpow(3, pow3 - 1, 1e18);

  if (rem == 0) return;

  while (rem % lpow(2, pow2, 1e18) == 0) pow2++;
  dissect(opow2 + pow2 - 1, rem / lpow(2, pow2 - 1, 1e18));
}

int main() {
  fast_io();

  ll t, n;
  cin >> t;

  while (t--) {
    ans.clear();

    cin >> n;
    int opow2 = 1;
    while (n % lpow(2, opow2, 1e18) == 0) opow2++;
    dissect(opow2 - 1, n / lpow(2, opow2 - 1, 1e18));

    int pow2, pow3;
    cout << ans.size() << '\n';
    for (auto pair : ans) {
      tie(pow2, pow3) = pair;
      cout << pow2 << ' ' << pow3 << '\n';
    }
  }
}
