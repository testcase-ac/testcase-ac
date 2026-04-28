#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e4;
int nums[MAX], smap[MAX + 1], sinv[MAX];
pii ans[MAX];
int main() {
  fast_io();

  int n, x, next, cnt = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i];
  for (int i = 0; i < n; i++) cin >> x, smap[x] = i, sinv[i] = x;
  for (int i = 0; i < n; i++) nums[i] = smap[nums[i]];

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

  vector<int> ax;
  while (!s.empty()) {
    ax.push_back(sinv[s.top()]);
    s.pop();
  }
  sort(ax.begin(), ax.end());

  for (int el : ax) cout << el << ' ';
}
