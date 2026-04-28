#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[100000];
ll pf_sums[100001];

int main() {
  fast_io();

  int n, s;
  ll* lbp;
  cin >> n >> s;
  for (int i = 0; i < n; i++) cin >> nums[i];

  pf_sums[0] = 0;
  for (int i = 0; i < n; i++) pf_sums[i + 1] = pf_sums[i] + nums[i];

  ll min_dist = 1e5 + 1;
  for (int i = 0; i < n + 1; i++) {
    lbp = lower_bound(pf_sums + i, pf_sums + n + 1, pf_sums[i] + s);
    if (lbp != pf_sums + n + 1) min_dist = min(min_dist, (ll)(lbp - pf_sums - i));
  }

  cout << (min_dist == 1e5 + 1 ? 0 : min_dist) << '\n';
}
