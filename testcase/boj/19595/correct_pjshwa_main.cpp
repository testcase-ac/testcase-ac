#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
bool d[MAX + 1];
ll lp[MAX + 1];
vector<int> pr;

void solve() {
  int A, k;
  cin >> A >> k;

  int mv = 0, mx = A - k + 1;
  for (int i = A - k + 1; i <= A; i++) mv += !d[i];
  
  int cur = mv;
  for (int x = A - k; x >= 2; x--) {
    cur -= !d[x + k];
    cur += !d[x];
    if (cur >= mv) {
      mv = cur;
      mx = x;
    }
  }

  cout << mv << ' ' << mx << '\n';
}

int main() {
  fast_io();

  for (ll i = 2; i <= MAX; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAX; j++)
      lp[i * pr[j]] = pr[j];
  }

  for (int p : pr) d[p] = d[p + 1] = true;
  for (int i = 2; i <= MAX; i++) {
    if (d[i]) continue;

    for (int p : pr) {
      if (p > i) break;
      if (!d[i - p]) {
        d[i] = true;
        break;
      }
    }
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
