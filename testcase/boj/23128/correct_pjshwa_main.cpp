#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX + 1], tally[MAX + 1];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i], tally[a[i]]++;

  int ans = 0;
  for (ll i = 1; i <= MAX; i++) {
    for (ll j = 1; j <= MAX; j++) {
      ll target = (i + j) * (i + j) - i * i;
      if (target > MAX) break;

      if (tally[i] && tally[target]) ans++;
    }
  }

  cout << ans << '\n';
}
