#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e3;
int a[MAX], dl[MAX], dr[MAX];

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  dl[0] = dr[n - 1] = 1;
  for (int i = 1; i < n; i++) dl[i] = a[i] > a[i - 1] ? dl[i - 1] + 1 : 1;
  for (int i = n - 2; i >= 0; i--) dr[i] = a[i] > a[i + 1] ? dr[i + 1] + 1 : 1;

  int ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, dl[i] + dr[i] - 1);
  cout << ans << '\n';
}
