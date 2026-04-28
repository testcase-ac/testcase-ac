#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2000;
vector<ll> p[10];
ll d[MAX + 1];

void solve() {
  int N, K;
  cin >> N >> K;
  for (int i = 0; i < N; i++) {
    int c, g;
    cin >> c >> g;
    p[g - 1].push_back(c);
  }
  for (int g = 0; g < 10; g++) {
    sort(p[g].begin(), p[g].end());
    reverse(p[g].begin(), p[g].end());

    for (int i = 1; i < p[g].size(); i++) {
      p[g][i] = p[g][i] + p[g][i - 1] + 2 * i;
    }
  }

  for (int g = 0; g < 10; g++) for (int s = K; s >= 0; s--) for (int u = 1; u <= p[g].size(); u++) {
    if (s + u <= K) d[s + u] = max(d[s + u], d[s] + p[g][u - 1]);
    else break;
  }
  cout << d[K] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
