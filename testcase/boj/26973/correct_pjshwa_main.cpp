#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

const int MAX = 1e5, MAXV = 5e6, INF = 0x3f3f3f3f;
int a[MAX], L[MAXV + 1];

vector<int> pr;
ll lp[MAXV + 1];

int f(int v) {
  if (v % 4 == 0) return v / 4;
  return v / 4 + 1;
}

void solve() {
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> a[i];

  int jval = INF, nval = INF, jocc, nocc;
  for (int i = 0; i < N; i++) {
    if (a[i] % 4 == 0) {
      if (f(a[i]) < nval) {
        nval = f(a[i]);
        nocc = i;
      }
    }
    else {
      int u = a[i] - L[a[i]];
      if (f(u) + 1 < jval) {
        jval = f(u) + 1;
        jocc = i;
      }
    }
  }

  if (jval == nval + 1) {
    if (jocc < nocc) cout << "Farmer John\n";
    else cout << "Farmer Nhoj\n";
  }
  else if (jval > nval) cout << "Farmer Nhoj\n";
  else cout << "Farmer John\n";
}

int main() {
  fast_io();

  // Sieve of Eratosthenes O(n)
  for (ll i = 2; i <= MAXV; ++i) {
    if (lp[i] == 0) {
      lp[i] = i;
      pr.push_back(i);
    }
    for (int j = 0; j < pr.size() && pr[j] <= lp[i] && i * pr[j] <= MAXV; j++)
      lp[i * pr[j]] = pr[j];
  }

  int max1 = 0, max2 = 2, max3 = 0;
  L[1] = 1;
  for (int i = 2; i <= MAXV; i++) {
    if (i % 4 == 0) continue;

    if (lp[i] == i) {
      if (i % 4 == 1) max1 = i;
      else max3 = i;
    }

    if (i % 4 == 1) L[i] = max1;
    if (i % 4 == 2) L[i] = max2;
    if (i % 4 == 3) L[i] = max3;
  }

  int t = 1;
  cin >> t;
  while (t--) solve();
}
