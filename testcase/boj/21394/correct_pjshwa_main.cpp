#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int a[9];
int u[1000];

void solve() {
  for (int i = 0; i < 9; i++) cin >> a[i];
  a[8] += a[5], a[5] = 0;

  priority_queue<int> pq;
  for (int i = 0; i < 9; i++) while (a[i]--) pq.push(i + 1);

  int n = pq.size();
  int sp = 0, ep = n - 1;
  while (!pq.empty()) {
    u[sp++] = pq.top(), pq.pop();
    if (!pq.empty()) u[ep--] = pq.top(), pq.pop();
  }

  for (int i = 0; i < n; i++) cout << u[i] << ' ';
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
