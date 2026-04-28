#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int n, G, k;
ll S[MAX], L[MAX], O[MAX];

bool feasible(ll d) {
  priority_queue<ll> out;
  __int128_t TG = 0, CG;
  for (int i = 0; i < n; i++) {
    CG = S[i] * max(1LL, d - L[i]);
    TG += CG;
    if (O[i]) out.push(CG);
  }
  for (int i = 0; i < k; i++) {
    if (out.empty()) break;
    TG -= out.top();
    out.pop();
  }
  return TG <= G;
}

void solve() {
  cin >> n >> G >> k;
  for (int i = 0; i < n; i++) cin >> S[i] >> L[i] >> O[i];

  ll left = 1, right = 4e9;
  while (left < right) {
    ll mid = (left + right) / 2;
    if (feasible(mid)) left = mid + 1;
    else right = mid;
  }

  cout << left - 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
