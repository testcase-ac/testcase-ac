#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e6;
int rem[MAX + 1];
int main() {
  fast_io();

  int T, n, ai, bi, ci;
  cin >> T >> n;

  priority_queue<pii> pq;
  for (int i = 0; i < n; i++) {
    cin >> ai >> bi >> ci;
    rem[ai] = bi;
    pq.push({ci, -ai});
  }

  for (int i = 0; i < T; i++) {
    auto [cc, ca] = pq.top();
    pq.pop();
    cout << -ca << '\n';
    if (--rem[-ca]) pq.push({--cc, ca});
  }

}
