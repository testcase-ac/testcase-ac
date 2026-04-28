#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int k[1000];
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

  int n, q, u, v;
  cin >> n >> q >> u >> v;
  for (int i = 0; i < n; i++) cin >> k[i], k[i] = u * k[i] + v;

  while (q--) {
    int c, a, b;
    cin >> c >> a >> b;

    if (c == 0) cout << max_subarray(a - 1, b - 1) - v << '\n';
    if (c == 1) k[a - 1] = u * b + v;
  }
}
