#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll mobius[200001];
ll squarefree_upto(ll n) {
  ll cnt = 0;
  for (ll i = 1; i * i <= n; i++) cnt += (mobius[i] * (n / (i * i)));
  return n - cnt;
}

int main() {
  // Precompute Mobius function values
  for (int i = 1; i <= 200000; i++) mobius[i] = 1;
  for (int i = 2; i * i <= 200000; i++) {
    if (mobius[i] == 1) {
      for (int j = i; j <= 200000; j += i) mobius[j] *= -i;
      for (int j = i * i; j <= 200000; j += i * i) mobius[j] = 0;
    }
  }
  for (int i = 2; i <= 200000; i++) {
    if (mobius[i] == i) mobius[i] = 1;
    else if (mobius[i] == -i) mobius[i] = -1;
    else if (mobius[i] < 0) mobius[i] = 1;
    else if (mobius[i] > 0) mobius[i] = -1;
  }

  ll n;
  cin >> n;

  ll left = 1;
  ll right = 4e10;
  ll mid = (left + right) / 2;

  while (left < right) {
    if (squarefree_upto(mid) < n) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  cout << mid << '\n';
}
