#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
ll d[MAX + 1];
vector<int> T[MAX + 1];

int tc;
void solve() {
  cout << "Case " << ++tc << ": ";

  for (int m = 1; m <= MAX; m++) T[m].clear();

  int S, N;
  cin >> S >> N;
  for (int i = 0; i < N; i++) {
    int vi, ci;
    cin >> vi >> ci;
    for (int m = 1; m <= ci; m++) T[m].push_back(vi * m);
  }

  ll ans = 0;

  // m: number of different values
  for (int m = 1; m <= MAX; m++) {
    memset(d, 0, sizeof(d));
    d[0] = 1;
    for (int v : T[m]) for (int i = S; i >= v; i--) d[i] += d[i - v];
    ans += d[S];
  }
  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
