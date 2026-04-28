#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 5e5;
int a[MAX], b[MAX], c[MAX];

void solve() {
  int n;
  cin >> n;
  priority_queue<pii> pq;
  for (int i = 0; i < n; i++) cin >> a[i], pq.push({a[i], i});
  for (int i = 0; i < n; i++) cin >> b[i], c[i] = b[i];
  sort(c, c + n);

  int d = n - 1;
  while (d > 0 && b[d] == c[d]) d--;

  for (int i = n - 1; i > d; i--) {
    while (pq.top().second > i) pq.pop();

    if (pq.top().second != i) {
      int j = pq.top().second;
      swap(a[i], a[j]);
      pq.pop();
      pq.push({a[j], j});
    }
  }

  for (int i = 0; i < n; i++) if (a[i] != b[i]) return cout << "0\n", void();
  cout << "1\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
