#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
 
void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int n, ans;
ll a[100];
ll d[100][21];

ll r(int pos, int target) {
  if (pos == n - 1) return target == ans;

  if (d[pos][target] == -1) {
    ll mv = 0;
    if (target + a[pos + 1] <= 20) mv += r(pos + 1, target + a[pos + 1]);
    if (target - a[pos + 1] >= 0) mv += r(pos + 1, target - a[pos + 1]);
    d[pos][target] = mv;
  }
  return d[pos][target];
}

int main() {
  fast_io();

  cin >> n;
  n--;
  for (int i = 0; i < n; i++) cin >> a[i];
  cin >> ans;

  memset(d, -1, sizeof(d));

  cout << r(0, a[0]);
}
