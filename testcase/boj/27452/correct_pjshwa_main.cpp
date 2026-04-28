#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAXZ = 87;
ll Sz[MAXZ + 1];

void solve() {
  ll n, k; cin >> n >> k;
  if (n > MAXZ) {
    ll D;
    if (n & 1) D = MAXZ;
    else D = MAXZ - 1;

    ll dif = n - D;
    if (k <= dif / 2) return cout << "(\n", void();
    else k -= dif / 2, n = D;
    assert(dif % 2 == 0);
  }

  if (k > Sz[n]) return cout << "0\n", void();
  while (n > 2) {
    if (k == 1) return cout << "(\n", void();
    if (k == Sz[n]) return cout << ")\n", void();

    if (k <= 1 + Sz[n - 2]) k -= 1, n -= 2;
    else k -= (1 + Sz[n - 2]), n -= 1;
  }

  if (k == 1) cout << "(\n";
  else if (k == 2) cout << ")\n";
  else assert(false);
}

int main() {
  fast_io();

  Sz[1] = Sz[2] = 2;
  for (int i = 3; i <= MAXZ; ++i) {
    Sz[i] = Sz[i - 1] + Sz[i - 2] + 2;
    // cout << "i = " << i << ", Sz[" << i << "] = " << Sz[i] << endl;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
