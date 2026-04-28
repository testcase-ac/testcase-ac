#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int N;
  cin >> N;

  vector<ll> wait(N);
  ll msz = 0, csz = 2, ans = 0;
  for (int i = 0; i < N; i++) {
    cin >> wait[i];
    msz = max(msz, wait[i]);
  }
  sort(wait.begin(), wait.end());

  priority_queue<ll> avail; int l = 0;
  while (l < N && wait[l] < csz) avail.push(wait[l++]);

  if (csz >= msz) return cout << ans << '\n', void();

  while (!avail.empty()) {
    ll w = avail.top(); avail.pop();
    csz += w; ans++;
    if (csz >= msz) return cout << ans << '\n', void();

    while (l < N && wait[l] < csz) avail.push(wait[l++]);
  }

  cout << "NIE\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
