#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int c[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n * (n - 1) / 2; i++) cin >> c[i];
  sort(c, c + n * (n - 1) / 2);

  ll mc = 0, xc = 0;
  for (int i = 0; i < n - 1; i++) mc += c[i];
  
  int g = 0;
  for (int i = 0; i < n - 1; i++) {
    xc += c[i + g];
    g += i;
  }

  cout << mc << ' ' << xc << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
