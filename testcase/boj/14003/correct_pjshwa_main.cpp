#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[(size_t)1e6];
pii ans[(size_t)1e6];
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
    else if (next > lis_vector.back()) {
      lis_vector.push_back(next);
      ans[i] = {++cnt, next};
    }
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next - 1);
      *it = next;
      ans[i] = {it - lis_vector.begin(), next};
    }
  }

  cout << cnt + 1 << '\n';

  int t = cnt;
  stack<int> s;

  for (int i = n - 1; i >= 0; i--) {
    if (ans[i].first == t) {
      s.push(ans[i].second);
      t--;
    }
  }

  while (!s.empty()) {
    cout << s.top() << ' ';
    s.pop();
  }

  cout << '\n';
}
