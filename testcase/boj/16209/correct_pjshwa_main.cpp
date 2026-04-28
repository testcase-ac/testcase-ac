#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[(size_t)5e5];
int main() {
  fast_io();

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) cin >> nums[i];
  sort(nums, nums + n);

  deque<int> po, ne;
  int rp = 0;
  while (rp < n && nums[rp] <= 0) rp++;

  for (int i = 0; i < rp; i++) {
    if (i & 1) ne.push_back(nums[i]);
    else ne.push_front(nums[i]);
  }
  for (int i = n - 1; i >= rp; i--) {
    if (i & 1) po.push_back(nums[i]);
    else po.push_front(nums[i]);
  }

  if (ne.size() && ne[0] > ne[rp - 1]) reverse(ne.begin(), ne.end());
  if (po.size() && po[0] > po[n - rp - 1]) reverse(po.begin(), po.end());

  for (auto el : ne) cout << el << ' ';
  for (auto el : po) cout << el << ' ';
  cout << '\n';
}
