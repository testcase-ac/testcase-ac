#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int booths[100000];
int main() {
  fast_io();

  int n, m;
  cin >> n >> m;

  for (int i = 0; i < n; i++) cin >> booths[i];

  ll left = 0, right = 1e18;
  ll mid = (left + right) >> 1;
  ll cur_s = 0;

  while (left < right) {
    for (int i = 0; i < n; i++) {
      cur_s += (mid / booths[i]);
      if (cur_s >= m) break;
    }

    if (cur_s >= m) right = mid;
    else left = mid + 1;

    cur_s = 0;
    mid = (left + right) >> 1;
  }

  cout << mid << '\n';
}
