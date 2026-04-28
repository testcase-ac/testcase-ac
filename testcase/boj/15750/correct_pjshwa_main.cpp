#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
map<int, int> cdt;

int main() {
  fast_io();

  int n;
  ll f = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int ai, bi;
    cin >> ai >> bi;
    f += abs(ai - bi);
    
    int d = max(0, abs(ai - bi) - abs(ai));
    cdt[bi] += 2;
    cdt[bi - d]--;
    cdt[bi + d]--;
  }

  ll ans = f, slope = 0, y = -2e9;
  for (auto [k, v] : cdt) {
    f += slope * (k - y);
    y = k;
    slope += v;
    ans = min(f, ans);
  }

  cout << ans << '\n';
}
