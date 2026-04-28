#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;
using tll = tuple<ll, ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 16;
int a[MAX];
double d[1 << MAX];

double area(int a, int b, int c) {
  int u[3] = {a, b, c};
  sort(u, u + 3);
  if (u[0] + u[1] <= u[2]) return 0;

  double p = (a + b + c) / 2.0;
  return sqrt(p * (p - a) * (p - b) * (p - c));
}

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];

  for (int state = 0; state < (1 << n); state++) {
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) for (int k = j + 1; k < n; k++) {
      if (!(state & (1 << i)) || !(state & (1 << j)) || !(state & (1 << k))) continue;
      d[state] = max(d[state], d[state ^ (1 << i) ^ (1 << j) ^ (1 << k)] + area(a[i], a[j], a[k]));
    }
  }

  cout << fixed << setprecision(10) << d[(1 << n) - 1] << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
