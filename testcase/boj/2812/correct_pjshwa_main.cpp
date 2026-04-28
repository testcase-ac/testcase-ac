#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int main() {
  fast_io();

  string s, r;
  int n, k;
  cin >> n >> k >> s;

  priority_queue<pii> pq;
  for (int i = 0; i < k; i++) pq.push({s[i], n - i});

  int li = n + 1;
  char c;
  for (int i = k; i < n; i++) {
    pq.push({s[i], n - i});
    while (pq.top().second >= li) pq.pop();
    tie(c, li) = pq.top();
    pq.pop();

    r += c;
  }
  cout << r;
}
