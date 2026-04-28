#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e6;
vector<int> pr;
int lp[MAX + 1], C[MAX + 1];

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int N, M, x; cin >> N >> M;

  while (N--) {
    cin >> x;
    while (x > 1) {
      C[lp[x]]++;
      x /= lp[x];
    }
  }
  while (M--) {
    cin >> x;
    while (x > 1) {
      C[lp[x]]--;
      x /= lp[x];
    }
  }

  ll X = 1, Y = 1;
  for (int i = 2; i <= MAX; i++) {
    if (C[i] > 0) {
      for (int j = 0; j < C[i]; j++) X *= i;
    }
    if (C[i] < 0) {
      for (int j = 0; j < -C[i]; j++) Y *= i;
    }
    C[i] = 0;
  }

  cout << X << " / " << Y << '\n';
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
