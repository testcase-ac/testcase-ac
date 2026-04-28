#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];

int main() {
  fast_io();

  int n, b, p;
  cin >> n >> b;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (a[i] == b) p = i;
  }

  map<int, int> dt;
  dt[0] = 1;
  int cdt = 0;
  for (int i = p + 1; i < n; i++) {
    if (a[i] < b) cdt--;
    else cdt++;
    dt[cdt]++;
  }

  ll ans = dt[0];
  cdt = 0;
  for (int i = p - 1; i >= 0; i--) {
    if (a[i] < b) cdt--;
    else cdt++;
    ans += dt[-cdt];
  }

  cout << ans << '\n';
}
