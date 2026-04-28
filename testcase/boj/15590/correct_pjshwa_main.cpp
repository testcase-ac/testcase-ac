#include <bits/stdc++.h>
typedef long long ll;
#define pll pair<ll, ll>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
ll prod[MAX];
pll store[MAX], buy[MAX];

int main() {
  fast_io();

  int n, m, r;
  cin >> n >> m >> r;
  for (int i = 0; i < n; i++) cin >> prod[i];
  for (int i = 0; i < m; i++) cin >> store[i].second >> store[i].first;
  for (int i = 0; i < r; i++) cin >> buy[i].first;

  sort(prod, prod + n);
  sort(buy, buy + r, greater<pll>());
  sort(store, store + m, greater<pll>());

  ll cv = 0;
  int sp = 0;
  for (int i = 0; i < min(n, r); i++) cv += buy[i].first, buy[i].second = prod[i];
  for (int i = min(n, r); i < n; i++) {
    ll gal = prod[i];
    while (gal) {
      if (sp == m) break;
      ll take = min(gal, store[sp].second);
      gal -= take;
      store[sp].second -= take;
      cv += store[sp].first * take;
      if (!store[sp].second) sp++;
    }
  }

  ll mv = cv;
  for (int i = min(n, r) - 1; i >= 0; i--) {
    cv -= buy[i].first;
    ll gal = buy[i].second;
    while (gal) {
      if (sp == m) break;
      ll take = min(gal, store[sp].second);
      gal -= take;
      store[sp].second -= take;
      cv += store[sp].first * take;
      if (!store[sp].second) sp++;
    }
    mv = max(mv, cv);
  }

  cout << mv;
}
