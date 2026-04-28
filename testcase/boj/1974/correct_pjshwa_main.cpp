#include <bits/stdc++.h>
using namespace std;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 10000;
int nums[MAX];
pii ans[MAX];

void solve() {
  int n, next, cnt = 0;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i], ans[i] = {0, 0};

  vector<int> lis_vector;
  lis_vector.push_back(nums[0]);
  ans[0] = {0, 0};

  for (int i = 1; i < n; i++) {
    next = nums[i];

    if (next < lis_vector[0]) {
      lis_vector[0] = next;
      ans[i] = {0, i};
    }
    else if (next > lis_vector.back()) {
      lis_vector.push_back(next);
      ans[i] = {++cnt, i};
    }
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next - 1);
      *it = next;
      ans[i] = {it - lis_vector.begin(), i};
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
    cout << s.top() + 1 << ' ';
    s.pop();
  }

  cout << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
