#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[(size_t)1e3];
int main() {
  fast_io();

  int n;
  cin >> n;

  int max_v = 0;
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
    max_v = max(max_v, nums[i]);
  }

  ll diffs = max_v - nums[0];
  for (int i = 0; i < n - 1; i++) diffs += max(0, nums[i] - nums[i + 1]);

  cout << diffs << '\n';
}
