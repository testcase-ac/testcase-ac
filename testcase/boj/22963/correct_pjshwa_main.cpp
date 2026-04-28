#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 2e5;
int nums[MAX];
pii ans[MAX];
int main() {
  fast_io();

  int n, next, cnt = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i];

  vector<int> lis_vector;
  lis_vector.push_back(nums[0]);
  ans[0] = {0, nums[0]};

  for (int i = 1; i < n; i++) {
    next = nums[i];

    if (next < lis_vector[0]) {
      lis_vector[0] = next;
      ans[i] = {0, next};
    }
    else if (next >= lis_vector.back()) {
      lis_vector.push_back(next);
      ans[i] = {++cnt, next};
    }
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next);
      *it = next;
      ans[i] = {it - lis_vector.begin(), next};
    }
  }

  if (cnt + 1 < n - 3) return cout << "NO", 0;

  int t = cnt;
  stack<int> s;

  for (int i = n - 1; i >= 0; i--) {
    if (ans[i].first == t) {
      s.push(ans[i].second);
      t--;
    }
  }

  vector<pair<int, int>> changes;
  int last = 1;
  for (int i = 0; i < n; i++) {
    if (!s.empty() && nums[i] == s.top()) {
      last = s.top();
      s.pop();
    }
    else changes.push_back({i + 1, last});
  }
  cout << "YES" << '\n';
  cout << changes.size() << '\n';
  for (auto p : changes) cout << p.first << ' ' << p.second << '\n';
}
