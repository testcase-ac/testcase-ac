#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const ll MAX = 2e6;
ll mobius[MAX + 1];
ll squarefree_upto(ll n) {
  ll cnt = 0;
  for (ll i = 1; i * i <= n; i++) cnt += (mobius[i] * (n / (i * i)));
  return cnt;
}

int main() {
  // Precompute Mobius function values
  for (int i = 1; i <= MAX; i++) mobius[i] = 1;
  for (int i = 2; i * i <= MAX; i++) {
    if (mobius[i] == 1) {
      for (int j = i; j <= MAX; j += i) mobius[j] *= -i;
      for (int j = i * i; j <= MAX; j += i * i) mobius[j] = 0;
    }
  }
  for (int i = 2; i <= MAX; i++) {
    if (mobius[i] == i) mobius[i] = 1;
    else if (mobius[i] == -i) mobius[i] = -1;
    else if (mobius[i] < 0) mobius[i] = 1;
    else if (mobius[i] > 0) mobius[i] = -1;
  }

  ll n;
  cin >> n;

  ll left = 1;
  ll right = MAX * MAX;
  ll mid = (left + right) / 2;

  while (left < right) {
    if (squarefree_upto(mid) < n) left = mid + 1;
    else right = mid;

    mid = (left + right) / 2;
  }

  cout << mid << '\n';
}
