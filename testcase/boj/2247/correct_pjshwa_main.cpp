#include <iostream>
using namespace std;

void fast_io() {
  cin.tie(NULL);
  ios_base::sync_with_stdio(false);
}

const int MOD = 1e6;
int main() {
  fast_io();

  int n;
  cin >> n;
  
  int ans = 0;
  long long i = 2;
  while (i < n) {
    long long sn = n / i;
    long long ln = n / sn;
    long long av = (ln * (ln + 1) / 2 - i * (i - 1) / 2) % MOD;
    av *= (sn - 1);
    ans = (ans + av) % MOD;
    i = ln + 1;
  }
  // for (int i = 2; i < n; i++) ans = (ans + i * (n / i - 1)) % MOD;
  cout << ans << '\n';
}
