#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
int a[MAX];
int tc;

void solve() {
  cout << "Case #" << ++tc << ": ";

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> a[i];
  sort(a, a + n);

  queue<int> q;
  for (int i = 0; i < n; i++) q.push(a[i]);

  int target = 1, ans = 0;
  while (1) {
    while (!q.empty() && q.front() < target) q.pop();
    if (q.empty()) break;

    q.pop();
    target++;
    ans++;
  }

  cout << ans << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
