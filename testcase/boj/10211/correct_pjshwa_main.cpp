#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

int n;
int k[1000];
const int INF = 1e9 + 7;

tuple<int, int, ll> max_subarray() {
  ll max_so_far = -INF, max_ending_here = 0;
  int ei;
  for (int i = 0; i < n; i++) {
    max_ending_here = max_ending_here + k[i];
    if (max_so_far < max_ending_here) ei = i + 1, max_so_far = max_ending_here;
    if (max_ending_here < 0) max_ending_here = 0;
  }
  ll s = 0;
  for (int si = ei - 1; si >= 0; si--) {
    s += k[si];
    if (s == max_so_far) return make_tuple(si, ei, max_so_far);
  }
}

void solve() {
  cin >> n;
  for (int i = 0; i < n; i++) cin >> k[i];
  auto [si, ei, max_so_far] = max_subarray();
  cout << max_so_far << '\n';
}

int main() {
  fast_io();

  int t;
  cin >> t;
  while (t--) solve();
}
