#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[(size_t)5e5];
int main() {
  fast_io();

  int n, m, s;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i];
  sort(nums, nums + n);

  cin >> m;
  for (int i = 0; i < m; i++) {
    cin >> s;
    cout << upper_bound(nums, nums + n, s) - lower_bound(nums, nums + n, s) << ' ';
  }
}
