#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

int main() {
  int t, n, m, s;
  cin >> t;

  while (t--) {
    queue<pii> q;
    priority_queue<pii> pq;

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
      cin >> s;
      pq.push({s, i});
      q.push({s, i});
    }

    while (!q.empty()) {
      if (q.front().first == pq.top().first) {
        if (q.front().second == m) cout << n - q.size() + 1 << '\n';
        q.pop();
        pq.pop();
      }
      else {
        q.push(q.front());
        q.pop();
      }
    }
  }
}
