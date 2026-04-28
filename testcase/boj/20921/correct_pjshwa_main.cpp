#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using tii = tuple<int, int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5000;
int a[MAX];

void solve() {
  int n, k;
  cin >> n >> k;

  for (int t = n; t >= 1; t--) {
    int rem = min(k, t - 1);
    int i = n - 1, c = 0;
    while (1) {
      if (a[i]) i--;
      else {
        if (c == rem) break;
        else i--, c++;
      }
    }
    k -= c;
    a[i] = t;
  }

  for (int i = 0; i < n; i++) cout << a[i] << " ";
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
//   cin >> t;
  while (t--) solve();
}
