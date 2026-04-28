#include <bits/stdc++.h>
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[(size_t)1e6];
int main() {
  FastIO();

  int t, n, m, x;
  cin >> t;

  while (t--) {
    cin >> n;
    for (int i = 0; i < n; i++) cin >> nums[i];
    sort(nums, nums + n);

    cin >> m;
    while (m--) {
      cin >> x;
      cout << (binary_search(nums, nums + n, x) ? 1 : 0) << '\n';
    }
  }
}
