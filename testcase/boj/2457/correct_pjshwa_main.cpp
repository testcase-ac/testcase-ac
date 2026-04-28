#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const int MAX = 1e5;
pii a[MAX];
int d[MAX];

void solve() {
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int m1, d1, m2, d2;
    cin >> m1 >> d1 >> m2 >> d2;
    for (int i = 1; i < m1; i++) d1 += days[i];
    for (int i = 1; i < m2; i++) d2 += days[i];
    a[i] = {max(60, d1) - 60, min(335, d2) - 61};
  }
  sort(a, a + n);

  int last = -1, si = 0, ans = 0;
  priority_queue<int> pq;
  while (si < n && a[si].first <= last + 1) {
    pq.push(a[si].second);
    si++;
  }

  while (!pq.empty()) {
    int cur = pq.top();
    pq.pop();

    if (cur > last) {
      last = cur;
      ans++;
      while (si < n && a[si].first <= last + 1) {
        pq.push(a[si].second);
        si++;
      }
    }
  }

  if (last == 274) cout << ans << '\n';
  else cout << "0\n";
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
