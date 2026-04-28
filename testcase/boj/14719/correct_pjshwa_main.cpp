#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(nullptr)->sync_with_stdio(false);
}

class Solution {
public:
  int trap(vector<int>& height) {
    int max_height = *max_element(height.begin(), height.end());
    int n = height.size();

    vector<int> max_indices;
    for (int i = 0; i < n; i++) {
      if (height[i] == max_height) max_indices.push_back(i);
    }

    int cur_max, ans = 0;

    cur_max = 0;
    for (int i = 0; i < max_indices[0]; i++) {
      if (height[i] > cur_max) cur_max = height[i];
      ans += cur_max - height[i];
    }

    cur_max = 0;
    for (int i = n - 1; i > max_indices.back(); i--) {
      if (height[i] > cur_max) cur_max = height[i];
      ans += cur_max - height[i];
    }

    for (int i = max_indices[0]; i < max_indices.back(); i++) {
      ans += max_height - height[i];
    }

    return ans;
  }
};

void solve() {
  int H, W;
  cin >> H >> W;

  vector<int> A(W);
  for (int i = 0; i < W; i++) cin >> A[i];

  cout << Solution().trap(A) << '\n';
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}
