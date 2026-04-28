#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int n;
ll p[MAX + 1], q[MAX + 1], r[MAX + 1], s[MAX + 1];

ll f(ll* ps) {
  ll ans = 0;
  for (int a = 1; a <= n; a++) ans += ps[a] * (2 * a - 1 - n);
  return ans * 2;
}

int main() {
  fast_io();

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> p[i], p[i] <<= 1;
  for (int i = 1; i <= n; i++) cin >> q[i], q[i] <<= 1;
  for (int i = 1; i <= n; i++) r[i] = (p[i] + q[i]) >> 1, s[i] = (p[i] - q[i]) >> 1;
  sort(p + 1, p + n + 1);
  sort(q + 1, q + n + 1);
  sort(r + 1, r + n + 1);
  sort(s + 1, s + n + 1);

  cout << (f(p) + f(q) - f(r) - f(s)) / 2;
}
