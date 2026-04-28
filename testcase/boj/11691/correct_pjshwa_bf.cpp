#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll mod = 1000000007;
ll lcm(ll x, ll y) { return x / __gcd(x, y) * y; }
ll all_pair_lcm(int n) {
    ll ans = 0;
    for (int i=1; i<=n-1; i++) {
        for (int j=i+1; j<=n; j++) {
            ans += lcm(i, j);
            ans %= mod;
        }
    }
    return ans;
}

int main() {
  int n;
  cin >> n;
  cout << all_pair_lcm(n) << '\n';
}

