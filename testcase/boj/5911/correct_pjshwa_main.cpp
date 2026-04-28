#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int p[MAX], s[MAX];

void solve() {
  int n, ob;
  cin >> n >> ob;
  for (int i = 0; i < n; i++) cin >> p[i] >> s[i];

  int ans = 0;
  for (int i = 0; i < n; i++) {
    vector<int> ps(n);
    for (int j = 0; j < n; j++) {
      if (i == j) ps[j] = p[j] / 2 + s[j];
      else ps[j] = p[j] + s[j];
    }
    sort(ps.begin(), ps.end());

    int b = ob, cnt = 0;
    for (int j = 0; j < n; j++) {
      if (b >= ps[j]) cnt++, b -= ps[j];
      else break;
    }

    ans = max(ans, cnt);
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
