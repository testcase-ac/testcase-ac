#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[(size_t)1e5];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;
  if (n < 2 || m == 0) {
    cout << "0\n";
    return 0;
  }

  for (int i = 0; i < n; i++) cin >> nums[i];
  sort(nums, nums + n);

  int min_diff = 2e9 + 1;
  int diff, x1 = 0, x2 = 1;

  while (min_diff > m && x2 < n) {
    diff = nums[x2] - nums[x1];
    if (diff < m) x2++;
    else {
      min_diff = min(diff, min_diff);
      x1++;
    }
  }

  cout << min_diff << '\n';
}
