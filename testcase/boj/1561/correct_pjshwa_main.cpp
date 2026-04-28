#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int m, r[10000];

// How many people have ridden the rides, after t minutes have passed?
ll c(ll t) {
  if (t == 0) return 0;

  ll n = 0;
  for (int i = 0; i < m; i++) n += ((t - 1) / r[i] + 1);
  return n;
}

int main() {
  fast_io();

  int n;
  cin >> n >> m;
  for (int i = 0; i < m; i++) cin >> r[i];

  if (n <= m) {
    cout << n;
    return 0;
  }

  ll left = 0, right = 6.1e10;
  ll mid = (left + right) / 2;

  while (left < right) {
    if (c(mid) <= n - 1) left = mid + 1;
    else right = mid;
 
    mid = (left + right) / 2;
  }

  ll t = mid - 1;
  ll current_completed = 0;
  for (int i = 0; i < m; i++) current_completed += ((t - 1) / r[i] + 1);
  n -= current_completed;
  for (int i = 0; i < m; i++) {
    if (t % r[i] == 0) n--;
    if (!n) {
      cout << i + 1;
      break;
    }
  }
}
