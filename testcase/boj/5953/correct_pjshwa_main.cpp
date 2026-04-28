#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int k[100000];
const int INF = 1e9 + 7;

ll max_subarray(int si, int ei) {
  ll max_so_far = -INF, max_ending_here = 0;
  for (int i = si; i <= ei; i++) {
    max_ending_here = max_ending_here + k[i];
    if (max_so_far < max_ending_here) max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;
  }
  return max_so_far;
}

int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> k[i];
  cout << max_subarray(0, n - 1) << '\n';
}
