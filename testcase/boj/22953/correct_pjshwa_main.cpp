#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10;
const ll INF = 1e13;
int n, k, c, a[MAX];
ll mv = INF;

void solve() {
  ll left = 1, right = INF;
  ll mid = (left + right) / 2;

  while (left < right) {
    ll sum = 0;
    for (int i = 0; i < n; i++) sum += (mid / a[i]);
    if (sum < k) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  mv = min(mv, mid);
}

void dfs() {
  if (c) {
    for (int i = 0; i < n; i++) {
      bool dec = a[i] > 1;
      if (dec) a[i]--;
      c--;
      dfs();
      c++;
      if (dec) a[i]++;
    }
  }
  else solve();
}

int main() {
  fast_io();

  cin >> n >> k >> c;
  for (int i = 0; i < n; i++) cin >> a[i];
  dfs();
  cout << mv;
}
