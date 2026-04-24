#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>
using namespace std;
#define int long long

int32_t main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  int x;
  deque<vector<int>> dq;
  int mn = 0;
  for (int t = 0; t < n; t++) {
    cin >> x;
    if (x < mn) {
      cout << t << '\n';
      return 0;
    }
    auto it = lower_bound(dq.begin(), dq.end(), x,
                          [](auto a, auto b) { return a[0] < b; });
    if (it == dq.end()) {
      // printf("at %lld, pushed new vector\n", x);
      dq.push_back({x});
      continue;
    }
    auto &v = *it;
    if (x < v.back()) {
      // printf("at %lld, direct push back at v[0] = %lld\n", x, v[0]);
      v.push_back(x);
      continue;
    }
    while (it != dq.begin()) {
      mn = max(dq[0][0], mn);
      dq.pop_front();
    }
    while (x > v.back()) {
      mn = max(mn, v.back());
      v.pop_back();
    }
    // printf("at %lld, erase and push back at v[0] = %lld. mn = %lld\n", x,
    // v[0], mn);
    v.push_back(x);
  }
  cout << n;
}
