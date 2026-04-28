#include <bits/stdc++.h>
#define pii pair<int, int>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums1[(size_t)1e5];
int nums2[(size_t)1e5];
int orders[(size_t)1e5 + 1];
int main() {
  fast_io();

  int n, next;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> nums1[i];
    orders[nums1[i]] = i;
  }
  for (int i = 0; i < n; i++) {
    cin >> next;
    nums2[i] = orders[next];
  }

  vector<int> lis_vector;
  lis_vector.push_back(-(1e9 + 1));

  for (int i = 0; i < n; i++) {
    next = nums2[i];

    if (next < lis_vector[0]) lis_vector[0] = next;
    else if (next > lis_vector.back()) lis_vector.push_back(next);
    else {
      auto it = upper_bound(lis_vector.begin(), lis_vector.end(), next - 1);
      *it = next;
    }
  }

  cout << lis_vector.size() - 1 << '\n';
}
