#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[3000];
ll pf_sums[3001];
int main() {
  fast_io();

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) cin >> nums[i];

  pf_sums[0] = 0;
  for (int i = 0; i < n; i++) pf_sums[i + 1] = pf_sums[i] + nums[i];

  int max_k = -1;
  ll min_v = 1e9 + 1;
  ll cur_v;
  for (int t = 1; t <= n / 2; t++) {
    for (int i = 0; i + t <= n; i++) {
      for (int j = i + t; j + t <= n; j++) {
        cur_v = abs(pf_sums[j + t] - pf_sums[j] - pf_sums[i + t] + pf_sums[i]);
        if (cur_v <= min_v) {
          min_v = cur_v;
          max_k = t;
        }
      }
    }
  }
  cout << max_k << '\n' << min_v << '\n';
}
