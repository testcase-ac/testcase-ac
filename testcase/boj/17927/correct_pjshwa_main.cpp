#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6, MOD = 1e9 + 7;
bool vis[MAX + 1];

int main() {
  fast_io();

  int n, l;
  cin >> n >> l;

  vector<int> gis(l + 1);
  gis[0] = 0;
  for (int i = 1; i <= l; i++) cin >> gis[i], vis[gis[i]] = true;
  for (int i = 1; i <= l; i++) if (gis[i] <= gis[i - 1]) return cout << "0\n", 0;

  ll ans = 1;
  int buc = 0, gp = gis.size() - 1;
  for (int i = n; i >= 1; i--) {
    if (vis[i]) continue;
    while (gis[gp] > i) gp--, buc++;

    ans = ans * buc % MOD;
    buc++;
  }

  cout << ans << '\n';
}
