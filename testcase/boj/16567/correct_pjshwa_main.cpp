#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define compress(x) sort(all(x)), (x).erase(unique(all(x)), (x).end())
#define getidx(v, x) (lower_bound(all(v), x) - v.begin())
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int a[MAX];

int main() {
  fast_io();

  int n, q;
  cin >> n >> q;

  int flips = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    if (!a[i]) continue;
    if (i == 0 || !a[i - 1]) flips++;
  }

  while (q--) {
    int op, b;
    cin >> op;
    if (op == 0) cout << flips << '\n';
    else {
      cin >> b;
      b--;
      if (a[b]) continue;
      a[b] = 1;

      int addend = 1;
      if (b > 0 && a[b - 1]) addend--;
      if (b < n - 1 && a[b + 1]) addend--;
      flips += addend;
    }
  }
}
