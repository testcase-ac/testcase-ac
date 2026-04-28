#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

int nums[(size_t)5e5];
int main() {
  fast_io();
  
  int n;
  cin >> n;

  ll sum = 0;
  for (int i = 0; i < n; i++) {
    cin >> nums[i];
    sum += nums[i];
  }

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    sum -= nums[i];
    ans += (nums[i] * sum);
  }

  cout << ans << '\n';
}
