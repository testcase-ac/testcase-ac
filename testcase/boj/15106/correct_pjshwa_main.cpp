#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll sumRange(ll a, ll b) {
  return (a + b) * (1 + b - a) / 2;
}

int main() {
  ll a, b, s = 0;
  cin >> a >> b;

  for (ll i = 1; i <= 1e6; i++) {
    ll an = ((a % i) ? a + i - (a % i) : a), bn = b - b % i;
    an = max(an, i * i);
    if (an > bn) continue;

    s += i * (bn / i - an / i + 1);
    s += sumRange(an / i, bn / i);
    if (an == i * i) s -= i;
  }

  cout << s;
}
