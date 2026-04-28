#include <bits/stdc++.h>
#define ll long long
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int main() {
  fast_io();

  ll n, k;
  cin >> n >> k;

  ll left = 1;
  ll right = n * n;
  ll mid = (left + right) / 2;

  while (left < right) {
    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += min(mid / i, n);
    if (sum < k) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  cout << mid << '\n';
}
