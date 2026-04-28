#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 1e5;
pii nums[MAX];
pii ans[MAX];
int main() {
  fast_io();

  int n, a, b, next, cnt = 0;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a >> b;
    nums[i] = {a, b};
  }
  sort(nums, nums + n);

  vector<int> lis_vector;
  lis_vector.push_back(nums[0].second);
  ans[0] = {0, nums[0].second};

  for (int i = 1; i < n; i++) {
    next = nums[i].second;

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

  cout << n - cnt - 1 << '\n';

  int t = cnt;
  set<int> s;

  for (int i = n - 1; i >= 0; i--) {
    if (ans[i].first == t) {
      s.insert(ans[i].second);
      t--;
    }
  }

  for (int i = 0; i < n; i++) if (!s.count(nums[i].second)) cout << nums[i].first << '\n';
}
