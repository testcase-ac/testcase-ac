#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
int n, tmax, a[MAX];

int ftime(int k) {
  priority_queue<int, vector<int>, greater<int>> pq;
  for (int i = 0; i < k; i++) pq.push(a[i]);

  int ai = k, res = 0;
  while (ai < n) {
    int t = pq.top();
    res = max(res, t);
    if (res > tmax) return tmax + 1;

    pq.pop();
    pq.push(t + a[ai]);
    ai++;
  }
  while (!pq.empty()) {
    res = max(res, pq.top());
    pq.pop();
  }

  return res;
}

void solve() {
  cin >> n >> tmax;
  for (int i = 0; i < n; i++) cin >> a[i];

  int left = 1, right = n + 1;
  while (left < right) {
    int mid = (left + right) / 2;
    if (ftime(mid) > tmax) left = mid + 1;
    else right = mid;
  }
  cout << left << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
