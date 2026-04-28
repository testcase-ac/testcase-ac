#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1000;
int a[MAX];

void solve() {
  int n, l;
  cin >> n >> l;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  int p = 0;
  queue<int> q;
  while (1) {
    while (p < n && a[p] <= l) {
      q.push(a[p]);
      p++;
    }
    if (q.empty()) break;
    l++;
    q.pop();
  }
  cout << l << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
