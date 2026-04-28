#include <bits/stdc++.h>
#define ll long long
using namespace std;

void FastIO() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

ll gcd(ll x, ll y){ return y ? gcd(y, x%y) : x; }

int main() {
  FastIO();

  int t, n;
  int nums[100];
  ll ans;
  cin >> t;

  while (t--) {
    cin >> n;
    ans = 0;
    for (int i = 0; i < n; i++) cin >> nums[i];

    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) ans += gcd(nums[i], nums[j]);
    }

    cout << ans << '\n';
  }
}
