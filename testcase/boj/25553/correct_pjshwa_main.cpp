#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 2e5;
int A[MAX];

void solve() {
  int N, Q, K;
  cin >> N >> Q >> K;
  for (int i = 0; i < N; i++) cin >> A[i];

  int pin = 0, pep = 0;
  ll cur = 0;
  for (int i = 0; i < K; i++) {
    if (i & 1) pep++;
    else pin++;
    cur += A[i];
  }

  map<pll, pll> u;
  u[{pin, pep}] = {cur, 0};
  pin--;
  cur -= A[0];

  for (int i = 0; i < N; i++) {
    int ni = (i + K) % N;

    if (ni & 1) pep++;
    else pin++;
    cur += A[ni];

    if (u.count({pin, pep})) {
      if (cur > u[{pin, pep}].first) {
        u[{pin, pep}] = {cur, i + 1};
      }
      else if (cur == u[{pin, pep}].first && i + 1 < u[{pin, pep}].second) {
        u[{pin, pep}].second = i + 1;
      }
    }
    else u[{pin, pep}] = {cur, i + 1};

    if (i == N - 1) break;

    if (i & 1) pin--;
    else pep--;
    cur -= A[i + 1];
  }

  ll a1 = 0, a2 = 0;
  while (Q--) {
    int op;
    cin >> op;
    if (op == 1) {
      int t;
      cin >> t;
      a1 += t;
    }
    if (op == 2) {
      int t;
      cin >> t;
      a2 += t;
    }
    if (op == 3) {
      ll midx = 1e18, mval = -1e18;
      for (auto [k, v] : u) {
        int pin, pep;
        ll cur, idx;
        tie(pin, pep) = k;
        tie(cur, idx) = v;

        ll nval = cur + pin * a1 + pep * a2;
        if (mval < nval || (mval == nval && midx > idx)) {
          mval = cur + pin * a1 + pep * a2;
          midx = idx;
        }
      }

      cout << midx + 1 << ' ' << mval << '\n';
    }
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
