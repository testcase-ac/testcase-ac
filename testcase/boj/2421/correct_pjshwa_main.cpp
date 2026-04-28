#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int d[MAX][MAX];

bool is_prime(ll n) {
  if (n <= 1) return false;
  if (n == 2) return true;
  if (n % 2 == 0) return false;

  for (ll i = 3; i * i <= n; i += 2) {
    if (n % i == 0) return false;
  }
  return true;
}

void solve() {
  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
    bool prime = is_prime(stoi(to_string(i) + to_string(j)));
    if (i == 1 && j == 1) d[i][j] = 0;
    else if (i == 1) d[i][j] = d[i][j - 1] + prime;
    else if (j == 1) d[i][j] = d[i - 1][j] + prime;
    else d[i][j] = max(d[i - 1][j], d[i][j - 1]) + prime;
  }

  cout << d[n][n] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
