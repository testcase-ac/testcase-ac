#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int pl[MAX], pr[MAX];
int u[2 * MAX];

void solve() {
  int n, carry, d; string s;
  cin >> n >> s;

  pl[0] = s[0] == '0' ? 0 : 1;
  for (int i = 1; i < n; i++) pl[i] = pl[i - 1] + (s[i] == '0' ? 0 : 1);
  pr[n - 1] = s[n - 1] == '0' ? 0 : 1;
  for (int i = n - 2; i >= 0; i--) pr[i] = pr[i + 1] + (s[i] == '0' ? 0 : 1);

  carry = 0;
  for (int i = 0; i < n; i++) {
    u[i] = pr[n - i - 1] + carry;
    carry = u[i] / 2, u[i] %= 2;
  }
  for (int i = 0; i < n - 1; i++) {
    u[n + i] = pl[n - i - 2] + carry;
    carry = u[n + i] / 2, u[n + i] %= 2;
  }
  u[2 * n - 1] = carry, d = 2 * n - 1;
  while (d >= 0 && u[d] == 0) d--;
  if (d == -1) d++;
  cout << d + 1 << ' ';

  pl[0] = s[0] == '1' ? 1 : 0;
  for (int i = 1; i < n; i++) pl[i] = pl[i - 1] + (s[i] == '1' ? 1 : 0);
  pr[n - 1] = s[n - 1] == '1' ? 1 : 0;
  for (int i = n - 2; i >= 0; i--) pr[i] = pr[i + 1] + (s[i] == '1' ? 1 : 0);

  carry = 0;
  for (int i = 0; i < n; i++) {
    u[i] = pr[n - i - 1] + carry;
    carry = u[i] / 2, u[i] %= 2;
  }
  for (int i = 0; i < n - 1; i++) {
    u[n + i] = pl[n - i - 2] + carry;
    carry = u[n + i] / 2, u[n + i] %= 2;
  }
  u[2 * n - 1] = carry, d = 2 * n - 1;
  while (d >= 0 && u[d] == 0) d--;
  if (d == -1) d++;
  cout << d + 1 << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
