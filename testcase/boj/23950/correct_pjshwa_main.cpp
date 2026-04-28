#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int tc;
void solve() {
  cout << "Case #" << ++tc << ": ";

  int n, hindex = 0;
  cin >> n;

  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < n; i++) {
    int x;
    cin >> x;
    pq.push(x);

    while (1) {
      while (!pq.empty() && pq.top() < hindex) pq.pop();
      if (pq.size() < hindex) break;
      hindex++;
    }

    cout << hindex - 1 << " ";
  }
  cout << '\n';
}

int main() {
  fast_io();

  int t = 1;
  cin >> t;
  while (t--) solve();
}
