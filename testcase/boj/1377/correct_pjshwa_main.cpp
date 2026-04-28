#include <bits/stdc++.h>
#define pii pair<int, int>
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

  vector<pii> nums_with_index;
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
    nums_with_index.push_back({ nums[i], i });
  }

  sort(nums_with_index.begin(), nums_with_index.end());

  int ans = 0;
  for (int i = 0; i < n; i++) ans = max(ans, nums_with_index[i].second - i);
  cout << ans + 1 << '\n';
}
