#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

const int MAX = 2e5, MOD = 1e9 + 7;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int N, Q;
  cin >> N >> Q;

  vector<ll> A(N);
  for (int i = 0; i < N; i++) cin >> A[i];

  map<ll, int> ax, dx;
  for (int i = 1; i < N; i++) {
    ax[A[i] - A[i - 1]]++;

    ll s;
    if (A[i] % A[i - 1]) s = -1;
    else s = A[i] / A[i - 1];
    dx[s]++;
  }

  while (Q--) {
    ll i, x;
    cin >> i >> x;
    i--;

    if (i < N - 1) {
      ll pa1 = A[i + 1] - A[i];
      ll ps1;
      if (A[i + 1] % A[i]) ps1 = -1;
      else ps1 = A[i + 1] / A[i];

      ax[pa1]--; dx[ps1]--;
      if (!ax[pa1]) ax.erase(pa1);
      if (!dx[ps1]) dx.erase(ps1);
    }

    if (i) {
      ll pa2 = A[i] - A[i - 1];
      ll ps2;
      if (A[i] % A[i - 1]) ps2 = -1;
      else ps2 = A[i] / A[i - 1];

      ax[pa2]--; dx[ps2]--;
      if (!ax[pa2]) ax.erase(pa2);
      if (!dx[ps2]) dx.erase(ps2);
    }

    A[i] = x;

    if (i < N - 1) {
      ll na1 = A[i + 1] - A[i];
      ll ns1;
      if (A[i + 1] % A[i]) ns1 = -1;
      else ns1 = A[i + 1] / A[i];

      ax[na1]++; dx[ns1]++;
    }

    if (i) {
      ll na2 = A[i] - A[i - 1];
      ll ns2;
      if (A[i] % A[i - 1]) ns2 = -1;
      else ns2 = A[i] / A[i - 1];

      ax[na2]++; dx[ns2]++;
    }

    if (ax.size() == 1 && ax.begin()->first > 0) cout << "+\n";
    else if (dx.size() == 1 && dx.begin()->first > 0) cout << "*\n";
    else cout << "?\n";
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
