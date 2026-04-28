#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  ll n, S; cin >> n >> S;
  bool neg = S < 0; S = abs(S);

  vector<int> A(n);
  iota(A.begin(), A.end(), 0);

  ll sum = n * (n - 1) / 2;
  if ((sum & 1) != (S & 1) || sum < S) return cout << "NIE\n", []{}();

  ll ded = 0, rem = sum - S;
  for (int i = 1; i < n; i++) {
    ll dif = 2 * (n - i);
    if (dif <= rem) {
      ded += 2;
      rem -= dif;
    }
    A[i] -= ded;
  }
  assert(rem == 0);

  for (int i = 0; i < n; i++) {
    if (neg) A[i] = -A[i];
    cout << A[i] << '\n';
  }

}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
