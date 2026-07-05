#include <bits/stdc++.h> 
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

void solve() {
  int n, m;
  cin >> n >> m;

  ll dam = 0;
  vector<pii> rem;
  for (int i = 0; i < n; i++) {
    int ti, hi;
    cin >> ti >> hi;
    hi = min(hi, m);

    if (ti <= hi) dam += (hi - ti);
    else rem.push_back({ti, ti - hi});
  }

  sort(rem.begin(), rem.end());
  while (!rem.empty()) {
    auto [ti, df] = rem.back();
    if (df <= dam) dam -= df;
    else {
      ll ded = min((ll)df, dam);
      dam -= ded; df -= ded; ti -= ded;

      if (ti <= m) m -= df;
      else return cout << "NO\n", void();
    }
    rem.pop_back();
  }

  cout << "YES\n";
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
