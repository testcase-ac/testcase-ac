#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

const int MAX = 1e7;
ll mobius[MAX + 1];

// number of ordered pairs of co-prime integers (x, y) such that 1 <= x <= a, 1 <= y <= b
ll coprime_cnt(int a, int b) {
  ll ans = 0;
  for (int k = 1; k <= min(a, b); k++) {
    ans += mobius[k] * (a / k) * (b / k);
  }
  return ans;
}

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

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

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  ll ans = coprime_cnt(b, d) - coprime_cnt(a - 1, d) - coprime_cnt(b, c - 1) + coprime_cnt(a - 1, c - 1);
  cout << ans << '\n';
}
