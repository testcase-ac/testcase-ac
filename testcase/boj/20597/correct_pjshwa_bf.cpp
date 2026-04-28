#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

void solve() {
  int n, k;
  cin >> n >> k;

  int p[n];
  for (int i = 0; i < n; i++) p[i] = i;

  int cnt = 0;
  do {
    bool invo = true;
    for (int i = 0; i < n; i++) {
      if (p[p[i]] != i) {
        invo = false;
        break;
      }
    }
    if (!invo) continue;

    int inv = 0;
    for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) {
      if (p[i] > p[j]) inv++;
    }
    if (inv == k) cnt++;

  } while (next_permutation(p, p + n));

  cout << cnt << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
