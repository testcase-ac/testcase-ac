#include <iostream>

const int MOD = int(1e9) + 7;

const int MAX_RADIUS = 450;
const int MAX_SUM = MAX_RADIUS * (MAX_RADIUS+1) / 2;

int ways[MAX_RADIUS+1][MAX_SUM+1];
int pref[MAX_RADIUS+1][MAX_SUM+1];

int main() {
  ways[0][0] = 1;
  for (int r = 1; r <= MAX_RADIUS; r++) {
    for (int i = 0; i <= r*(r+1)/2; i++) {
      ways[r][i] = (ways[r-1][i] + (i >= r ? ways[r-1][i-r] : 0)) % MOD;
    }
    for (int i = 0; i <= r*(r+1)/2; i++) {
      pref[r][i] = (((i >= 1) ? pref[r][i-1] : 0) + ways[r][i]) % MOD;
    }
  }

  int Q; std::cin >> Q;
  for (int q = 0; q < Q; q++) {
    int a, b; std::cin >> a >> b;

    long long ans = 0;

    for (int i = 1; i <= MAX_RADIUS; i++) {
      int l = std::max(i * (i+1) / 2 - b, 0);
      int r = std::min(a, i * (i+1) / 2);
      if (l <= r) {
        ans += pref[i][r];
        ans += MOD - (l == 0 ? 0 : pref[i][l-1]);
      }
    }

    ans %= MOD;
    std::cout << ans << "\n";
  }
  return 0;
}