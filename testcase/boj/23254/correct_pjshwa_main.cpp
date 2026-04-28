#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
pii a[MAX];

int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  priority_queue<pair<int, int>> pq;
  for (int i = 0; i < m; i++) cin >> a[i].second;
  for (int i = 0; i < m; i++) cin >> a[i].first;
  for (int i = 0; i < m; i++) pq.push(a[i]);

  n *= 24;
  int sum = 0;

  while (!pq.empty() && n) {
    auto p = pq.top();
    pq.pop();

    int rem = 100 - p.second;
    int pay = min(n, rem / p.first);
    n -= pay;

    pair<int, int> np = p;
    np.second += pay * p.first;
    if (np.second == 100) sum += 100; 
    else pq.push({min(100 - np.second, p.first), np.second});
  }

  while (!pq.empty()) {
    sum += pq.top().second;
    pq.pop();
  }
  cout << sum << '\n';
}
