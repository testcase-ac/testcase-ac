#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[1000];
int main() {
  fast_io();

  int n;
  cin >> n;

  vector<int> sums;
  for (int i = 0; i < n; i++) cin >> nums[i];
  for (int i = 0; i < n; i++) {
    for (int j = i; j < n; j++) sums.push_back(nums[i] + nums[j]);
  }
  sort(sums.begin(), sums.end());
  sort(nums, nums + n);
  
  int mx = 0;
  for (int i = n - 1; i >= 0; i--) {
    for (int j = i - 1; j >= 0; j--) {
      if (
        upper_bound(sums.begin(), sums.end(), nums[i] - nums[j]) -
        lower_bound(sums.begin(), sums.end(), nums[i] - nums[j])
      ) mx = max(nums[i], mx);
    }
  }

  cout << mx << '\n';
}
