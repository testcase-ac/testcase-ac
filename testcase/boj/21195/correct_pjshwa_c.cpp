#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  int n, s, a;
  cin >> n >> s;

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < n; i++) {
    cin >> a;
    pq.push({a, i});
  }

  int mx = 0;
  for (int i = 1; i <= n; i++) {
    while (pq.top().second < i) {
      int vv = pq.top().first;
      pq.pop();
      pq.push({vv + n * s, n});
    }
    mx = max(mx, pq.top().first - i * s);
  }

  cout << mx;
}
