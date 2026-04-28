#include <bits/stdc++.h>
#define pii pair<int, int>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5, INF = 1e9 + 7;
int a[MAX];

int main() {
  fast_io();

  int n, s = 0;
  cin >> n;
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  for (int i = 0; i < n; i++) cin >> a[i], s += a[i], pq.push({a[i], i});

  ll max_sum = 0, max_div = 1;
  for (int i = 1; i <= n - 2; i++) {
    s -= a[i - 1];
    while (pq.top().second < i) pq.pop();

    ll cur_sum = s - pq.top().first, cur_div = n - i - 1;
    if (max_sum * cur_div < cur_sum * max_div) {
      max_sum = cur_sum;
      max_div = cur_div;
    }
  }

  while (!pq.empty()) pq.pop();
  s = 0;
  for (int i = 0; i < n; i++) s += a[i], pq.push({a[i], i});

  for (int i = 1; i <= n - 2; i++) {
    s -= a[i - 1];
    while (pq.top().second < i) pq.pop();

    ll cur_sum = s - pq.top().first, cur_div = n - i - 1;
    if (max_sum * cur_div == cur_sum * max_div) cout << i << '\n';
  }
}
