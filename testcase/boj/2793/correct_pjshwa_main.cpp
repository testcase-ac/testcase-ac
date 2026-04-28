#include <iostream>
typedef long long ll;
using namespace std;

ll strength_upto(ll n) {
  // odds
  ll ans = ((n + 1) / 2) * 2;

  // even
  ans += (n / 2) * 3;
  ans += (((n / 6) + 1) / 2);
  ans += (((n / 420) + 1) / 2);
  ans += (((n / 360360) + 1) / 2);
  ans += (((n / 72201776446800) + 1) / 2);

  return ans;
}

int main() {
  ll a, b;
  cin >> a >> b;
  cout << strength_upto(b) - strength_upto(a - 1) << '\n';
}
