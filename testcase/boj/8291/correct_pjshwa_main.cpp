#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

const int MAX = 3e6;
int tally[MAX + 1], mobius[MAX + 1];

int main() {
  fast_io();
  
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

  int n, x;
  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> x;
    tally[x]++;
  }

  ll ans = 0;
  for (int i = 1; i <= MAX; i++) {
    int ccnt = 0;
    for (int j = i; j <= MAX; j += i) ccnt += tally[j];
    ans += ((ll)mobius[i] * ccnt * (ccnt - 1) / 2);
  }

  cout << ans << '\n';
}
