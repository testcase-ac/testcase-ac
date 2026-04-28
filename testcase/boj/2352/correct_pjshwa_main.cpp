#include <bits/stdc++.h>
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int nums[40000];
int main() {
  fast_io();

  int n, next;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i];

  vector<int> lis_vector;
  lis_vector.push_back(-(1e9 + 1));

  for (int i = 0; i < n; i++) {
    next = nums[i];

    if (next < lis_vector[0]) lis_vector[0] = next;
    else if (next > lis_vector.back()) lis_vector.push_back(next);
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next - 1);
      *it = next;
    }
  }

  cout << lis_vector.size() - 1;
}
