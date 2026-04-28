#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll G = 1, L = 1, x, o;

  map<ll, int> t;
  cin >> x; while (x--) cin >> o, t[o]--, G *= o;
  cin >> x; while (x--) cin >> o, t[o]++, L *= o;

  vector<ll> A;
  for (auto& [k, v] : t) {
    ll p = 1;
    for (int i = 0; i < v; i++) p *= k;
    A.push_back(p);
  }

  int N = A.size();
  vector<ll> P1{1}, P2{1};
  for (int i = 0; i < N / 2; i++) {
    ll x = A[i], z = P1.size();
    for (int j = 0; j < z; j++) P1.push_back(P1[j] * x);
  }
  for (int i = N / 2; i < N; i++) {
    ll x = A[i], z = P2.size();
    for (int j = 0; j < z; j++) P2.push_back(P2[j] * x);
  }
  sort(P1.begin(), P1.end());
  sort(P2.begin(), P2.end());

  int z1 = P1.size(), z2 = P2.size(), r = z2 - 1;
  ll sum = 1e18, mc, md, O = L / G;
  for (int l = 0; l < z1; l++) {
    while (r >= 0) {
      ll cc = P1[l] * P2[r], cd = O / cc;
      if (cc > cd) {
        r--;
        continue;
      }

      if (r > 0) {
        ll nc = P1[l] * P2[r - 1], nd = O / nc;
        if (nc + nd <= cc + cd) {
          r--;
          continue;
        }
      }
      break;
    }
    if (r < 0) break;

    ll cc = P1[l] * P2[r], cd = O / cc;
    if (cc + cd < sum) {
      sum = cc + cd;
      mc = cc, md = cd;
    }
    else if (cc + cd == sum && cc < mc) {
      mc = cc, md = cd;
    }
  }

  cout << mc * G << ' ' << md * G << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
