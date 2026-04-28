#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
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

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  string S; ll N;
  cin >> S >> N;
  int z = S.size();

  ll T[3] = {0}, U[z];
  for (int i = 0; i < z; i++) {
    if (S[i] == 'W') U[i] = 0;
    if (S[i] == 'R') U[i] = 1;
    if (S[i] == 'G') U[i] = 2;
  }

  int pw = 0;
  while (N) {
    int r = N % 3;

    while (r--) {
      ll g = lpow(3, pw, z);

      int nu[z];
      for (int i = 0; i < z; i++) {
        nu[i] = (U[i] + U[(i + g) % z]) % 3;
      }
      for (int i = 0; i < z; i++) U[i] = nu[i];
    }

    N /= 3;
    pw++;
  }

  for (int i = 0; i < z; i++) T[U[i]]++;
  for (int i = 0; i < 3; i++) cout << T[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
